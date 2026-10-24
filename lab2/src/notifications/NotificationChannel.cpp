#include "../../include/notifications/NotificationChannel.h"

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

}
