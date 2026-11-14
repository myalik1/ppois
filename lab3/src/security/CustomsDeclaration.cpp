#include "../../include/security/CustomsDeclaration.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kPercentDivisor = 100.0;
}

CustomsDeclaration::CustomsDeclaration(const std::string& declarationId,
                                       const Passenger& passenger,
                                       double declaredGoodsValueUsd,
                                       bool carriesRestrictedItems)
    : declarationId_(declarationId),
      passengerId_(passenger.getPassengerId()),
      declaredGoodsValueUsd_(declaredGoodsValueUsd),
      carriesRestrictedItems_(carriesRestrictedItems),
      isApproved_(false) {}

double CustomsDeclaration::calculateCustomsDutyUsd(double dutyFreeLimitUsd,
                                                   double dutyRatePercent) const {
    if (declaredGoodsValueUsd_ <= dutyFreeLimitUsd || dutyRatePercent <= 0.0) {
        return 0.0;
    }
    return (declaredGoodsValueUsd_ - dutyFreeLimitUsd) * (dutyRatePercent / kPercentDivisor);
}

void CustomsDeclaration::inspectAndApprove(const BaggageItem& baggage,
                                           double maxAllowedWeightKg) {
    if (carriesRestrictedItems_) {
        throw SecurityBreachException("Restricted items prohibited by customs");
    }
    baggage.checkWeightLimit(maxAllowedWeightKg);
    isApproved_ = true;
}

bool CustomsDeclaration::requiresRedChannel(double dutyFreeLimitUsd) const {
    return carriesRestrictedItems_ || declaredGoodsValueUsd_ > dutyFreeLimitUsd;
}

const std::string& CustomsDeclaration::getDeclarationId() const { return declarationId_; }
const std::string& CustomsDeclaration::getPassengerId() const { return passengerId_; }
double CustomsDeclaration::getDeclaredGoodsValueUsd() const { return declaredGoodsValueUsd_; }
bool CustomsDeclaration::getCarriesRestrictedItems() const { return carriesRestrictedItems_; }
bool CustomsDeclaration::getIsApproved() const { return isApproved_; }

}
