#include "../../include/documents/DocumentCore.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const int kHighConfidentialityThreshold = 7;
const int kMaxSecurityLevel = 10;
const long kDefaultTimestamp = 1000L;
}

Tag::Tag(std::string name, std::string category, int confidentialityWeight)
    : tagName_(std::move(name)),
      categoryName_(std::move(category)),
      confidentialityWeight_(confidentialityWeight) {}

bool Tag::isHighConfidentiality() const {
    return confidentialityWeight_ >= kHighConfidentialityThreshold;
}

bool Tag::matchesCategory(const std::string& category) const {
    return categoryName_ == category;
}

const std::string& Tag::getTagName() const {
    return tagName_;
}

Attachment::Attachment(
    std::string fileName, std::string mimeType, std::size_t sizeBytes, std::string hash)
    : fileName_(std::move(fileName)),
      mimeType_(std::move(mimeType)),
      fileSizeBytes_(sizeBytes),
      checksum_(std::move(hash)) {}

bool Attachment::verifyChecksum(const std::string& expectedHash) const {
    return !expectedHash.empty() && checksum_ == expectedHash;
}

bool Attachment::exceedsSizeLimit(std::size_t maxBytes) const {
    return fileSizeBytes_ > maxBytes;
}

const std::string& Attachment::getFileName() const {
    return fileName_;
}

DocumentMetadata::DocumentMetadata(
    long createdTs, long modifiedTs, std::string lang, int securityLevel)
    : createdTimestamp_(createdTs),
      modifiedTimestamp_(modifiedTs),
      languageCode_(std::move(lang)),
      securityLevel_(securityLevel) {}

void DocumentMetadata::updateModificationTime(long newTimestamp) {
    if (newTimestamp < createdTimestamp_) {
        throw InvalidDocumentDataException("Modification timestamp precedes creation");
    }
    modifiedTimestamp_ = newTimestamp;
}

void DocumentMetadata::escalateSecurityLevel(int deltaLevel) {
    int updatedLevel = securityLevel_ + deltaLevel;
    if (deltaLevel <= 0 || updatedLevel > kMaxSecurityLevel) {
        throw InvalidDocumentDataException("Invalid security escalation level");
    }
    securityLevel_ = updatedLevel;
}

int DocumentMetadata::getSecurityLevel() const {
    return securityLevel_;
}

long DocumentMetadata::getModifiedTimestamp() const {
    return modifiedTimestamp_;
}

DocumentVersion::DocumentVersion(
    int versionNumber, std::string authorId, std::string body, std::string summary)
    : versionNumber_(versionNumber),
      authorId_(std::move(authorId)),
      contentBody_(std::move(body)),
      changeSummary_(std::move(summary)) {}

std::size_t DocumentVersion::calculateContentLength() const {
    return contentBody_.size();
}

bool DocumentVersion::containsKeyword(const std::string& keyword) const {
    return !keyword.empty() && contentBody_.find(keyword) != std::string::npos;
}

int DocumentVersion::getVersionNumber() const {
    return versionNumber_;
}

const std::string& DocumentVersion::getContentBody() const {
    return contentBody_;
}

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
