#pragma once

#include "../documents/Document.h"
#include <cstddef>
#include <string>
#include <vector>

namespace docflow {

class Folder {
public:
    Folder(std::string folderId, std::string folderName);
    void putDocument(const Document& document);
    void removeDocumentId(const std::string& documentId);
    std::size_t countDocuments() const;

private:
    std::string folderId_;
    std::string folderName_;
    std::vector<std::string> documentIds_;
};

}
