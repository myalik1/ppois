#include "../../include/storage/DocumentRepository.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

DocumentRepository::DocumentRepository(std::string name, StorageLocation location)
    : repositoryName_(std::move(name)), location_(std::move(location)) {}

void DocumentRepository::saveDocument(const Document& document, std::size_t sizeBytes) {
    const std::string& docId = document.getDocumentId();
    if (docId.empty()) {
        throw InvalidDocumentDataException("Document ID cannot be empty when saving");
    }
    location_.allocateSpace(sizeBytes);
    documents_[docId] = document;
}

Document DocumentRepository::findDocument(const std::string& documentId) const {
    auto it = documents_.find(documentId);
    if (it == documents_.end()) {
        throw DocumentNotFoundException("Document not found in repository");
    }
    return it->second;
}

void DocumentRepository::deleteDocument(const std::string& documentId, std::size_t sizeBytes) {
    auto it = documents_.find(documentId);
    if (it == documents_.end()) {
        throw DocumentNotFoundException("Cannot delete missing document");
    }
    documents_.erase(it);
    location_.releaseSpace(sizeBytes);
}

std::size_t DocumentRepository::countStoredDocuments() const {
    return documents_.size();
}

}
