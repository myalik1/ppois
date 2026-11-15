#include "../../include/passengers/LoyaltyCard.h"

namespace airport {

namespace {
const int kGoldTierMiles = 50000;
const int kSilverTierMiles = 20000;
const double kGoldDiscount = 0.15;
const double kSilverDiscount = 0.08;
const double kStandardDiscount = 0.02;
}

LoyaltyCard::LoyaltyCard(const std::string& cardNumber,
                         int milesBalance,
                         const std::string& tierLevel,
                         bool isActive)
    : cardNumber_(cardNumber),
      milesBalance_(milesBalance),
      tierLevel_(tierLevel),
      isActive_(isActive) {}

void LoyaltyCard::accrueMiles(int flownMiles) {
    if (isActive_ && flownMiles > 0) {
        milesBalance_ += flownMiles;
        recalculateTier();
    }
}

bool LoyaltyCard::redeemMiles(int milesToRedeem) {
    if (!isActive_ || milesToRedeem <= 0 || milesToRedeem > milesBalance_) {
        return false;
    }
    milesBalance_ -= milesToRedeem;
    recalculateTier();
    return true;
}

void LoyaltyCard::recalculateTier() {
    if (milesBalance_ >= kGoldTierMiles) {
        tierLevel_ = "GOLD";
    } else if (milesBalance_ >= kSilverTierMiles) {
        tierLevel_ = "SILVER";
    } else {
        tierLevel_ = "BRONZE";
    }
}

double LoyaltyCard::calculateDiscountRate() const {
    if (!isActive_) {
        return 0.0;
    }
    if (tierLevel_ == "GOLD") {
        return kGoldDiscount;
    }
    if (tierLevel_ == "SILVER") {
        return kSilverDiscount;
    }
    return kStandardDiscount;
}

const std::string& LoyaltyCard::getCardNumber() const { return cardNumber_; }
int LoyaltyCard::getMilesBalance() const { return milesBalance_; }
const std::string& LoyaltyCard::getTierLevel() const { return tierLevel_; }
bool LoyaltyCard::getIsActive() const { return isActive_; }

}
