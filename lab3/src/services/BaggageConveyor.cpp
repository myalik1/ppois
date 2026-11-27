#include "../../include/services/BaggageConveyor.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

BaggageConveyor::BaggageConveyor(const std::string& beltId,
                                 double maxLoadKg,
                                 bool isRunning)
    : beltId_(beltId),
      maxLoadKg_(maxLoadKg),
      currentLoadKg_(0.0),
      bagsOnBelt_(0),
      isRunning_(isRunning) {}

void BaggageConveyor::startBelt() {
    isRunning_ = true;
}

void BaggageConveyor::stopBelt() {
    isRunning_ = false;
}

void BaggageConveyor::loadBaggageOntoBelt(const BaggageItem& item) {
    if (!isRunning_) {
        throw AirportException("Conveyor belt is stopped");
    }
    if (currentLoadKg_ + item.getWeightKg() > maxLoadKg_) {
        throw BaggageOverweightException("Conveyor belt maximum weight capacity exceeded");
    }
    currentLoadKg_ += item.getWeightKg();
    ++bagsOnBelt_;
}

void BaggageConveyor::unloadAllBaggage() {
    currentLoadKg_ = 0.0;
    bagsOnBelt_ = 0;
}

const std::string& BaggageConveyor::getBeltId() const { return beltId_; }
double BaggageConveyor::getMaxLoadKg() const { return maxLoadKg_; }
double BaggageConveyor::getCurrentLoadKg() const { return currentLoadKg_; }
int BaggageConveyor::getBagsOnBelt() const { return bagsOnBelt_; }
bool BaggageConveyor::getIsRunning() const { return isRunning_; }

}
