#pragma once
#include <string>

namespace airport {

class SecurityBadge {
private:
    std::string badgeId_;
    std::string officerName_;
    int clearanceLevel_;
    bool isActive_;

public:
    SecurityBadge(const std::string& badgeId,
                  const std::string& officerName,
                  int clearanceLevel,
                  bool isActive = true);

    bool verifyAccessZone(int requiredZoneLevel) const;
    void revokeBadge();
    void upgradeClearance(int newLevel);

    const std::string& getBadgeId() const;
    const std::string& getOfficerName() const;
    int getClearanceLevel() const;
    bool getIsActive() const;
};

}
