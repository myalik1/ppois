#pragma once
#include <string>

namespace airport {

class LoyaltyCard {
private:
    std::string cardNumber_;
    int milesBalance_;
    std::string tierLevel_;
    bool isActive_;

public:
    LoyaltyCard(const std::string& cardNumber,
                int milesBalance,
                const std::string& tierLevel,
                bool isActive);

    void accrueMiles(int flownMiles);
    bool redeemMiles(int milesToRedeem);
    void recalculateTier();
    double calculateDiscountRate() const;

    const std::string& getCardNumber() const;
    int getMilesBalance() const;
    const std::string& getTierLevel() const;
    bool getIsActive() const;
};

}
