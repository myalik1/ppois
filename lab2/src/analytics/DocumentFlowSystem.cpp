#include "../../include/analytics/DocumentFlowSystem.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const int kWriteAccessLevel = 2;
}

DocumentFlowSystem::DocumentFlowSystem(
    std::string systemName,
    AccessController accessController,
    DocumentRepository repository,
    WorkflowManager workflowManager,
    AuditLogger auditLogger)
    : systemName_(std::move(systemName)),
      accessController_(std::move(accessController)),
      repository_(std::move(repository)),
      workflowManager_(std::move(workflowManager)),
      auditLogger_(std::move(auditLogger)) {}

void DocumentFlowSystem::registerAndStoreDocument(
    const User& actor, const Document& document, std::size_t sizeBytes) {
    bool allowed = accessController_.verifyAccess(actor, "DOCUMENT", kWriteAccessLevel);
    if (!allowed) {
        throw UnauthorizedAccessException("User lacks permission to store documents");
    }
    repository_.saveDocument(document, sizeBytes);
    auditLogger_.recordAction(actor, document, "STORE_DOCUMENT");
}

void DocumentFlowSystem::initiateDocumentApproval(
    const User& actor, const std::string& documentId, const ApprovalRoute& route) {
    Document doc = repository_.findDocument(documentId);
    workflowManager_.startWorkflow(doc, route);
    repository_.deleteDocument(documentId, 1);
    repository_.saveDocument(doc, 1);
    auditLogger_.recordAction(actor, doc, "START_WORKFLOW");
}

void DocumentFlowSystem::approveDocumentInSystem(
    const User& actor, const std::string& documentId, const std::string& comment) {
    Document doc = repository_.findDocument(documentId);
    workflowManager_.submitApproval(doc, actor, comment);
    repository_.deleteDocument(documentId, 1);
    repository_.saveDocument(doc, 1);
    auditLogger_.recordAction(actor, doc, "APPROVE_DOCUMENT");
}

Document DocumentFlowSystem::getStoredDocument(const std::string& documentId) const {
    return repository_.findDocument(documentId);
}

std::size_t DocumentFlowSystem::getAuditCount() const {
    return auditLogger_.getEntriesCount();
}

}
