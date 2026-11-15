#include "../../include/passengers/BaggageTag.h"

namespace airport {

namespace {
const std::size_t kIataCodeLength = 3;
const std::size_t kMinTagCodeLength = 5;
}

BaggageTag::BaggageTag(const std::string& tagCode,
                       const std::string& destinationIata,
                       bool isPriority,
                       bool isScanned)
    : tagCode_(tagCode),
      destinationIata_(destinationIata),
      isPriority_(isPriority),
      isScanned_(isScanned) {}

void BaggageTag::markScanned() {
    isScanned_ = true;
}

bool BaggageTag::validateTagFormat() const {
    return tagCode_.length() >= kMinTagCodeLength &&
           destinationIata_.length() == kIataCodeLength;
}

bool BaggageTag::matchesDestination(const std::string& airportIata) const {
    return destinationIata_ == airportIata;
}

const std::string& BaggageTag::getTagCode() const { return tagCode_; }
const std::string& BaggageTag::getDestinationIata() const { return destinationIata_; }
bool BaggageTag::getIsPriority() const { return isPriority_; }
bool BaggageTag::getIsScanned() const { return isScanned_; }

}
