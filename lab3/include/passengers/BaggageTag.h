#pragma once
#include <string>

namespace airport {

class BaggageTag {
private:
    std::string tagCode_;
    std::string destinationIata_;
    bool isPriority_;
    bool isScanned_;

public:
    BaggageTag(const std::string& tagCode,
               const std::string& destinationIata,
               bool isPriority,
               bool isScanned = false);

    void markScanned();
    bool validateTagFormat() const;
    bool matchesDestination(const std::string& airportIata) const;

    const std::string& getTagCode() const;
    const std::string& getDestinationIata() const;
    bool getIsPriority() const;
    bool getIsScanned() const;
};

}
