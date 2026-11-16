#pragma once

#include "../documents/Document.h"
#include <string>

namespace docflow {

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

}
