#include "../../include/core/AccessController.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

AccessController::AccessController(std::string controllerId, bool strictMode)
    : controllerId_(std::move(controllerId)), strictMode_(strictMode) {}

void AccessController::assignRole(const User& user, const Role& role) {
    if (!user.isActive()) {
        throw UnauthorizedAccessException("Cannot assign role to inactive user");
    }
    const std::string& uid = user.getUserId();
    assignedRoles_[uid] = role;
}

bool AccessController::verifyAccess(
    const User& user, const std::string& resource, int level) const {
    if (!user.isActive()) {
        throw UnauthorizedAccessException("Inactive user access denied");
    }
    auto it = assignedRoles_.find(user.getUserId());
    if (it == assignedRoles_.end()) {
        if (strictMode_) {
            throw UnauthorizedAccessException("No role assigned to user");
        }
        return false;
    }
    return it->second.hasResourceAccess(resource, level);
}

void AccessController::revokeUserAccess(const std::string& userId) {
    auto it = assignedRoles_.find(userId);
    if (it == assignedRoles_.end()) {
        throw UnauthorizedAccessException("User role not found for revocation");
    }
    assignedRoles_.erase(it);
}

}
