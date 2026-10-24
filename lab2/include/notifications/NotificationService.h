#pragma once

#include "NotificationChannel.h"
#include "Notification.h"
#include "Subscription.h"
#include <cstddef>
#include <string>
#include <vector>

namespace docflow {

class NotificationService {
public:
    explicit NotificationService(NotificationChannel channel);
    void addSubscription(const Subscription& subscription);
    std::size_t notifySubscribers(const Document& document, const std::string& eventText);
    std::size_t countUnreadForUser(const User& user) const;

private:
    NotificationChannel channel_;
    std::vector<Notification> notifications_;
    std::vector<Subscription> subscriptions_;
};

}
