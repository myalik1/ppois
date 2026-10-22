#include "../include/exceptions/WorkflowExceptions.h"
#include "../include/notifications/NotificationSystem.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(NotificationSystemTest, SubscriptionsDeliveryAndReminders) {
    User subscriber("U1", "Sub User", "u@b.c", "D1", true);
    Document doc("DOC-9", "Policy", "U1", DocumentMetadata(1, 1, "RU", 1));

    NotificationChannel channel("EMAIL", "smtp.company.by", true);
    NotificationService service(channel);
    service.addSubscription(Subscription("U1", "DOC-9", true));

    std::size_t delivered = service.notifySubscribers(doc, "Document updated");
    EXPECT_EQ(delivered, 1U);
    EXPECT_EQ(service.countUnreadForUser(subscriber), 1U);

    Reminder reminder("REM-1", "DOC-9", "U1", 10);
    EXPECT_TRUE(reminder.isOverdue(15));
    reminder.reschedule(20);
    EXPECT_EQ(reminder.getDueHour(), 20);
    EXPECT_THROW(reminder.reschedule(10), InvalidDocumentDataException);
}

TEST(NotificationSystemTest, ChannelAndSubscriptionExceptions) {
    NotificationChannel channel("SMS", "123", true);
    EXPECT_FALSE(channel.canDeliverMessage(""));
    channel.disableChannel();
    EXPECT_FALSE(channel.canDeliverMessage("Hello"));

    Subscription sub("U1", "D1", true);
    sub.unsubscribe();
    Document doc("D1", "T", "U1", DocumentMetadata());
    EXPECT_FALSE(sub.matchesEvent(doc));

    NotificationService service(channel);
    EXPECT_THROW(service.notifySubscribers(doc, "MSG"), InvalidDocumentStateException);
    EXPECT_THROW(service.addSubscription(Subscription("", "D1", true)), InvalidDocumentDataException);
}

TEST(NotificationSystemTest, NotificationAndReminderBehaviors) {
    Notification notif("N1", "U1", "MSG", false);
    EXPECT_FALSE(notif.isRead());
    notif.markAsRead();
    EXPECT_TRUE(notif.isRead());

    Reminder rem("R1", "D1", "U1", 10);
    EXPECT_THROW(rem.reschedule(5), InvalidDocumentDataException);
}
