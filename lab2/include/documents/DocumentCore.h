#pragma once

#include "../core/IdentityAndAccess.h"
#include <cstddef>
#include <string>
#include <vector>

namespace docflow {

class Tag {
public:
    Tag(std::string name, std::string category, int confidentialityWeight);
    bool isHighConfidentiality() const;
    bool matchesCategory(const std::string& category) const;
    const std::string& getTagName() const;

private:
    std::string tagName_;
    std::string categoryName_;
    int confidentialityWeight_;
};

class Attachment {
public:
    Attachment(std::string fileName, std::string mimeType, std::size_t sizeBytes, std::string hash);
    bool verifyChecksum(const std::string& expectedHash) const;
    bool exceedsSizeLimit(std::size_t maxBytes) const;
    const std::string& getFileName() const;

private:
    std::string fileName_;
    std::string mimeType_;
    std::size_t fileSizeBytes_;
    std::string checksum_;
};

class DocumentMetadata {
public:
    DocumentMetadata() = default;
    DocumentMetadata(long createdTs, long modifiedTs, std::string lang, int securityLevel);
    void updateModificationTime(long newTimestamp);
    void escalateSecurityLevel(int deltaLevel);
    int getSecurityLevel() const;
    long getModifiedTimestamp() const;

private:
    long createdTimestamp_{0};
    long modifiedTimestamp_{0};
    std::string languageCode_{"RU"};
    int securityLevel_{1};
};

class DocumentVersion {
public:
    DocumentVersion(int versionNumber, std::string authorId, std::string body, std::string summary);
    std::size_t calculateContentLength() const;
    bool containsKeyword(const std::string& keyword) const;
    int getVersionNumber() const;
    const std::string& getContentBody() const;

private:
    int versionNumber_;
    std::string authorId_;
    std::string contentBody_;
    std::string changeSummary_;
};

class Document {
public:
    Document() = default;
    Document(std::string id, std::string title, std::string ownerId, DocumentMetadata metadata);
    void addNewVersion(const DocumentVersion& version);
    void attachFile(const Attachment& attachment);
    void applyTag(const Tag& tag);
    void transitionStatus(const std::string& nextStatus);
    const std::string& getDocumentId() const;
    const std::string& getTitle() const;
    const std::string& getStatus() const;
    const DocumentMetadata& getMetadata() const;
    const std::vector<DocumentVersion>& getVersions() const;
    const std::vector<Tag>& getTags() const;

private:
    std::string documentId_;
    std::string title_;
    std::string ownerId_;
    std::string status_{"DRAFT"};
    DocumentMetadata metadata_;
    std::vector<DocumentVersion> versions_;
    std::vector<Attachment> attachments_;
    std::vector<Tag> tags_;
};

class DocumentTemplate {
public:
    DocumentTemplate(std::string id, std::string name, std::string defaultBody, int securityLevel);
    Document instantiateDocument(
        const std::string& docId, const std::string& title, const User& owner) const;
    bool validatePlaceholder(const std::string& placeholder) const;

private:
    std::string templateId_;
    std::string templateName_;
    std::string defaultBody_;
    int requiredSecurityLevel_;
};

}
