#include "../../include/passengers/LostBaggageRecord.h"

namespace airport {

namespace {
const double kMaxCompensationCapUsd = 1500.0;
}

LostBaggageRecord::LostBaggageRecord(const std::string& claimId, const Passenger& passenger,
                                     const BaggageTag& tag, int daysMissing, bool isResolved)
    : claimId_(claimId), passengerId_(passenger.getPassengerId()), tagCode_(tag.getTagCode()),
      daysMissing_(daysMissing), isResolved_(isResolved) {}

void LostBaggageRecord::incrementMissingDays(int additionalDays) {
    if (!isResolved_ && additionalDays > 0) {
        daysMissing_ += additionalDays;
    }
}

double LostBaggageRecord::calculateCompensation(double dailyAllowanceUsd) const {
    if (isResolved_ || daysMissing_ <= 0 || dailyAllowanceUsd <= 0.0) {
        return 0.0;
    }
    double total = static_cast<double>(daysMissing_) * dailyAllowanceUsd;
    return total > kMaxCompensationCapUsd ? kMaxCompensationCapUsd : total;
}

void LostBaggageRecord::markFound(BaggageTag& tag) {
    if (tag.getTagCode() == tagCode_) {
        tag.markScanned();
        isResolved_ = true;
    }
}

const std::string& LostBaggageRecord::getClaimId() const { return claimId_; }
const std::string& LostBaggageRecord::getPassengerId() const { return passengerId_; }
const std::string& LostBaggageRecord::getTagCode() const { return tagCode_; }
int LostBaggageRecord::getDaysMissing() const { return daysMissing_; }
bool LostBaggageRecord::getIsResolved() const { return isResolved_; }

}
