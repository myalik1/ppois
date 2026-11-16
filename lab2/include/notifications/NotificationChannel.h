#pragma once

#include <string>

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

}
