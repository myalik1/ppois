#pragma once

#include "../core/User.h"
#include <string>

namespace docflow {

class Notification {
public:
    Notification(std::string id, std::string recipientId, std::string message, bool readFlag);
    void markAsRead();
    bool isForUser(const User& user) const;
    bool isRead() const;

private:
    std::string notificationId_;
    std::string recipientUserId_;
    std::string messageText_;
    bool readFlag_;
};

}
