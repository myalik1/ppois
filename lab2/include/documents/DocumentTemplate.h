#pragma once

#include "../core/User.h"
#include "Document.h"
#include <string>

namespace docflow {

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
