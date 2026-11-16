#pragma once

#include "../core/User.h"
#include "Document.h"
#include <string>

namespace docflow {

class MemoDocument {
public:
    MemoDocument(Document doc, std::string senderId, std::string recipientId, bool urgent);
    void escalateUrgency();
    bool isAddressedTo(const User& user) const;
    bool isUrgent() const;

private:
    Document baseDocument_;
    std::string senderUserId_;
    std::string recipientUserId_;
    bool urgentFlag_;
};

}
