#pragma once
#include <string>
#include "../passengers/Passenger.h"
#include "../passengers/BaggageItem.h"

namespace airport {

class CustomsDeclaration {
private:
    std::string declarationId_;
    std::string passengerId_;
    double declaredGoodsValueUsd_;
    bool carriesRestrictedItems_;
    bool isApproved_;

public:
    CustomsDeclaration(const std::string& declarationId,
                       const Passenger& passenger,
                       double declaredGoodsValueUsd,
                       bool carriesRestrictedItems);

    double calculateCustomsDutyUsd(double dutyFreeLimitUsd, double dutyRatePercent) const;
    void inspectAndApprove(const BaggageItem& baggage, double maxAllowedWeightKg);
    bool requiresRedChannel(double dutyFreeLimitUsd) const;

    const std::string& getDeclarationId() const;
    const std::string& getPassengerId() const;
    double getDeclaredGoodsValueUsd() const;
    bool getCarriesRestrictedItems() const;
    bool getIsApproved() const;
};

}
