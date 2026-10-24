#include "../../include/notifications/Notification.h"

namespace docflow {

Notification::Notification(
    std::string id, std::string recipientId, std::string message, bool readFlag)
    : notificationId_(std::move(id)),
      recipientUserId_(std::move(recipientId)),
      messageText_(std::move(message)),
      readFlag_(readFlag) {}

void Notification::markAsRead() {
    readFlag_ = true;
}

bool Notification::isForUser(const User& user) const {
    const std::string& uid = user.getUserId();
    return recipientUserId_ == uid;
}

bool Notification::isRead() const {
    return readFlag_;
}

}
