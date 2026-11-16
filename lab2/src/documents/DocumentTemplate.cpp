#include "../../include/documents/DocumentTemplate.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const long kDefaultTimestamp = 1000L;
}

DocumentTemplate::DocumentTemplate(
    std::string id, std::string name, std::string defaultBody, int securityLevel)
    : templateId_(std::move(id)),
      templateName_(std::move(name)),
      defaultBody_(std::move(defaultBody)),
      requiredSecurityLevel_(securityLevel) {}

Document DocumentTemplate::instantiateDocument(
    const std::string& docId, const std::string& title, const User& owner) const {
    if (!owner.isActive()) {
        throw UnauthorizedAccessException("Inactive owner cannot instantiate template");
    }
    DocumentMetadata meta(kDefaultTimestamp, kDefaultTimestamp, "RU", requiredSecurityLevel_);
    Document doc(docId, title, owner.getUserId(), meta);
    DocumentVersion initialVersion(1, owner.getUserId(), defaultBody_, "Created from template");
    doc.addNewVersion(initialVersion);
    return doc;
}

bool DocumentTemplate::validatePlaceholder(const std::string& placeholder) const {
    return !placeholder.empty() && defaultBody_.find(placeholder) != std::string::npos;
}

}
