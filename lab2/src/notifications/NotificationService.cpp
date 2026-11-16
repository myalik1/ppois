#include "../../include/notifications/NotificationService.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

NotificationService::NotificationService(NotificationChannel channel)
    : channel_(std::move(channel)) {}

void NotificationService::addSubscription(const Subscription& subscription) {
    if (subscription.getSubscriberUserId().empty()) {
        throw InvalidDocumentDataException("Subscriber user ID cannot be empty");
    }
    subscriptions_.push_back(subscription);
}

std::size_t NotificationService::notifySubscribers(
    const Document& document, const std::string& eventText) {
    if (!channel_.canDeliverMessage(eventText)) {
        throw InvalidDocumentStateException("Notification channel cannot deliver message");
    }
    std::size_t sentCount = 0;
    for (const auto& sub : subscriptions_) {
        if (sub.matchesEvent(document)) {
            std::string notifId = "NTF-" + std::to_string(notifications_.size() + 1);
            notifications_.emplace_back(notifId, sub.getSubscriberUserId(), eventText, false);
            sentCount += 1;
        }
    }
    return sentCount;
}

std::size_t NotificationService::countUnreadForUser(const User& user) const {
    std::size_t unreadCount = 0;
    for (const auto& notif : notifications_) {
        if (notif.isForUser(user) && !notif.isRead()) {
            unreadCount += 1;
        }
    }
    return unreadCount;
}

}
