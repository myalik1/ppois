#pragma once

#include "../audit/AuditLogger.h"
#include "../core/AccessController.h"
#include "../storage/DocumentRepository.h"
#include "../workflow/WorkflowManager.h"
#include <cstddef>
#include <string>

namespace docflow {

class DocumentFlowSystem {
public:
    DocumentFlowSystem(
        std::string systemName,
        AccessController accessController,
        DocumentRepository repository,
        WorkflowManager workflowManager,
        AuditLogger auditLogger);
    void registerAndStoreDocument(
        const User& actor, const Document& document, std::size_t sizeBytes);
    void initiateDocumentApproval(
        const User& actor, const std::string& documentId, const ApprovalRoute& route);
    void approveDocumentInSystem(
        const User& actor, const std::string& documentId, const std::string& comment);
    Document getStoredDocument(const std::string& documentId) const;
    std::size_t getAuditCount() const;

private:
    std::string systemName_;
    AccessController accessController_;
    DocumentRepository repository_;
    WorkflowManager workflowManager_;
    AuditLogger auditLogger_;
};

}
