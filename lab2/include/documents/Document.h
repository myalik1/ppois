#pragma once

#include "Attachment.h"
#include "DocumentMetadata.h"
#include "DocumentVersion.h"
#include "Tag.h"
#include <string>
#include <vector>

namespace docflow {

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

}
