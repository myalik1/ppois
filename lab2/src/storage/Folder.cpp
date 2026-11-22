#include "../../include/storage/Folder.h"
#include "../../include/exceptions/WorkflowExceptions.h"
#include <algorithm>

namespace docflow {

Folder::Folder(std::string folderId, std::string folderName)
    : folderId_(std::move(folderId)), folderName_(std::move(folderName)) {}

void Folder::putDocument(const Document& document) {
    const std::string& docId = document.getDocumentId();
    if (docId.empty()) {
        throw InvalidDocumentDataException("Cannot put document with empty ID into folder");
    }
    documentIds_.push_back(docId);
}

void Folder::removeDocumentId(const std::string& documentId) {
    auto it = std::find(documentIds_.begin(), documentIds_.end(), documentId);
    if (it == documentIds_.end()) {
        throw DocumentNotFoundException("Document ID not found in folder");
    }
    documentIds_.erase(it);
}

std::size_t Folder::countDocuments() const {
    return documentIds_.size();
}

}
