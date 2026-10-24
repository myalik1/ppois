#include "../../include/documents/MemoDocument.h"

namespace docflow {

MemoDocument::MemoDocument(Document doc, std::string senderId, std::string recipientId, bool urgent)
    : baseDocument_(std::move(doc)),
      senderUserId_(std::move(senderId)),
      recipientUserId_(std::move(recipientId)),
      urgentFlag_(urgent) {}

void MemoDocument::escalateUrgency() {
    urgentFlag_ = true;
}

bool MemoDocument::isAddressedTo(const User& user) const {
    const std::string& targetId = user.getUserId();
    return recipientUserId_ == targetId;
}

bool MemoDocument::isUrgent() const {
    return urgentFlag_;
}

}
