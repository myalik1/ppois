#include "../../include/security/SecurityBadge.h"

namespace airport {

namespace {
const int kMaxClearanceLevel = 5;
}

SecurityBadge::SecurityBadge(const std::string& badgeId,
                             const std::string& officerName,
                             int clearanceLevel,
                             bool isActive)
    : badgeId_(badgeId),
      officerName_(officerName),
      clearanceLevel_(clearanceLevel),
      isActive_(isActive) {}

bool SecurityBadge::verifyAccessZone(int requiredZoneLevel) const {
    return isActive_ && !badgeId_.empty() && clearanceLevel_ >= requiredZoneLevel;
}

void SecurityBadge::revokeBadge() {
    isActive_ = false;
}

void SecurityBadge::upgradeClearance(int newLevel) {
    if (newLevel > clearanceLevel_ && newLevel <= kMaxClearanceLevel) {
        clearanceLevel_ = newLevel;
    }
}

const std::string& SecurityBadge::getBadgeId() const { return badgeId_; }
const std::string& SecurityBadge::getOfficerName() const { return officerName_; }
int SecurityBadge::getClearanceLevel() const { return clearanceLevel_; }
bool SecurityBadge::getIsActive() const { return isActive_; }

}
