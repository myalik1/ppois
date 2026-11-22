#include "../../include/notifications/Subscription.h"

namespace docflow {

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

}
