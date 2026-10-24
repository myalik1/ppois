#include "../../include/documents/Document.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

Document::Document(std::string id, std::string title, std::string ownerId, DocumentMetadata metadata)
    : documentId_(std::move(id)),
      title_(std::move(title)),
      ownerId_(std::move(ownerId)),
      status_("DRAFT"),
      metadata_(std::move(metadata)) {}

void Document::addNewVersion(const DocumentVersion& version) {
    if (status_ == "ARCHIVED") {
        throw InvalidDocumentStateException("Cannot add version to archived document");
    }
    int expectedNumber = static_cast<int>(versions_.size()) + 1;
    if (version.getVersionNumber() != expectedNumber) {
        throw InvalidDocumentDataException("Non-sequential version number");
    }
    versions_.push_back(version);
}

void Document::attachFile(const Attachment& attachment) {
    if (attachment.getFileName().empty()) {
        throw InvalidDocumentDataException("Attachment file name is empty");
    }
    attachments_.push_back(attachment);
}

void Document::applyTag(const Tag& tag) {
    if (tag.getTagName().empty()) {
        throw InvalidDocumentDataException("Tag name cannot be empty");
    }
    tags_.push_back(tag);
}

void Document::transitionStatus(const std::string& nextStatus) {
    if (nextStatus.empty() || status_ == "ARCHIVED") {
        throw InvalidDocumentStateException("Illegal document status transition");
    }
    status_ = nextStatus;
}

const std::string& Document::getDocumentId() const {
    return documentId_;
}

const std::string& Document::getTitle() const {
    return title_;
}

const std::string& Document::getStatus() const {
    return status_;
}

const DocumentMetadata& Document::getMetadata() const {
    return metadata_;
}

const std::vector<DocumentVersion>& Document::getVersions() const {
    return versions_;
}

const std::vector<Tag>& Document::getTags() const {
    return tags_;
}

}
