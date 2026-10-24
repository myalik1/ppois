#pragma once

#include "../documents/Document.h"
#include "StorageLocation.h"
#include <cstddef>
#include <map>
#include <string>

namespace docflow {

class DocumentRepository {
public:
    DocumentRepository(std::string name, StorageLocation location);
    void saveDocument(const Document& document, std::size_t sizeBytes);
    Document findDocument(const std::string& documentId) const;
    void deleteDocument(const std::string& documentId, std::size_t sizeBytes);
    std::size_t countStoredDocuments() const;

private:
    std::string repositoryName_;
    StorageLocation location_;
    std::map<std::string, Document> documents_;
};

}
