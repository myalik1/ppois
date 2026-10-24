#include "../../include/notifications/NotificationSystem.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

NotificationChannel::NotificationChannel(
    std::string channelType, std::string endpoint, bool enabled)
    : channelType_(std::move(channelType)),
      endpointAddress_(std::move(endpoint)),
      enabledFlag_(enabled) {}

void NotificationChannel::disableChannel() {
    enabledFlag_ = false;
}

bool NotificationChannel::canDeliverMessage(const std::string& text) const {
    return enabledFlag_ && !endpointAddress_.empty() && !text.empty();
}

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

Subscription::Subscription(std::string subscriberId, std::string watchedDocId, bool active)
    : subscriberUserId_(std::move(subscriberId)),
      watchedDocumentId_(std::move(watchedDocId)),
      activeSubscription_(active) {}

void Subscription::unsubscribe() {
    activeSubscription_ = false;
}

bool Subscription::matchesEvent(const Document& document) const {
    const std::string& docId = document.getDocumentId();
    return activeSubscription_ && watchedDocumentId_ == docId;
}

const std::string& Subscription::getSubscriberUserId() const {
    return subscriberUserId_;
}

Reminder::Reminder(std::string id, std::string docId, std::string userId, int dueHour)
    : reminderId_(std::move(id)),
      documentId_(std::move(docId)),
      targetUserId_(std::move(userId)),
      dueHour_(dueHour) {}

bool Reminder::isOverdue(int currentHour) const {
    return currentHour > dueHour_;
}

void Reminder::reschedule(int newDueHour) {
    if (newDueHour <= dueHour_) {
        throw InvalidDocumentDataException("New due hour must be greater than current due hour");
    }
    dueHour_ = newDueHour;
}

int Reminder::getDueHour() const {
    return dueHour_;
}

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
