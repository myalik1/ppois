#pragma once

#include "../core/IdentityAndAccess.h"
#include "../documents/DocumentCore.h"
#include <cstddef>
#include <string>
#include <vector>

namespace docflow {

class NotificationChannel {
public:
    NotificationChannel(std::string channelType, std::string endpoint, bool enabled);
    void disableChannel();
    bool canDeliverMessage(const std::string& text) const;

private:
    std::string channelType_;
    std::string endpointAddress_;
    bool enabledFlag_;
};

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

class Subscription {
public:
    Subscription(std::string subscriberId, std::string watchedDocId, bool active);
    void unsubscribe();
    bool matchesEvent(const Document& document) const;
    const std::string& getSubscriberUserId() const;

private:
    std::string subscriberUserId_;
    std::string watchedDocumentId_;
    bool activeSubscription_;
};

class Reminder {
public:
    Reminder(std::string id, std::string docId, std::string userId, int dueHour);
    bool isOverdue(int currentHour) const;
    void reschedule(int newDueHour);
    int getDueHour() const;

private:
    std::string reminderId_;
    std::string documentId_;
    std::string targetUserId_;
    int dueHour_;
};

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
