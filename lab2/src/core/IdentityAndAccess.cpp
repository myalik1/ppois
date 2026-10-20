#include "../../include/core/IdentityAndAccess.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const int kMinAccessLevel = 1;
}

Permission::Permission(std::string code, std::string resource, int level)
    : permissionCode_(std::move(code)), resourceName_(std::move(resource)), accessLevel_(level) {}

bool Permission::grantsLevel(int requiredLevel) const {
    return requiredLevel >= kMinAccessLevel && accessLevel_ >= requiredLevel;
}

bool Permission::matchesResource(const std::string& resource) const {
    return !resource.empty() && resourceName_ == resource;
}

const std::string& Permission::getPermissionCode() const {
    return permissionCode_;
}

Role::Role(std::string name, int priorityRank)
    : roleName_(std::move(name)), priorityRank_(priorityRank) {}

void Role::addPermission(const Permission& permission) {
    if (permission.getPermissionCode().empty()) {
        throw InvalidDocumentDataException("Permission code cannot be empty");
    }
    permissions_.push_back(permission);
}

bool Role::hasResourceAccess(const std::string& resource, int level) const {
    for (const auto& perm : permissions_) {
        bool sameResource = perm.matchesResource(resource);
        bool enoughLevel = perm.grantsLevel(level);
        if (sameResource && enoughLevel) {
            return true;
        }
    }
    return false;
}

bool Role::canOverrideRole(const Role& otherRole) const {
    return priorityRank_ > otherRole.priorityRank_;
}

const std::string& Role::getRoleName() const {
    return roleName_;
}

Department::Department(std::string id, std::string name, std::string headUserId, int monthlyQuota)
    : departmentId_(std::move(id)),
      departmentName_(std::move(name)),
      headUserId_(std::move(headUserId)),
      monthlyQuota_(monthlyQuota) {}

void Department::consumeQuota(int documentCount) {
    if (documentCount <= 0 || documentCount > monthlyQuota_) {
        throw StorageCapacityExceededException("Department quota exceeded");
    }
    monthlyQuota_ -= documentCount;
}

bool Department::isHead(const std::string& userId) const {
    return !userId.empty() && headUserId_ == userId;
}

const std::string& Department::getDepartmentId() const {
    return departmentId_;
}

const std::string& Department::getDepartmentName() const {
    return departmentName_;
}

int Department::getMonthlyQuota() const {
    return monthlyQuota_;
}

User::User(std::string id, std::string fullName, std::string email, std::string deptId, bool active)
    : userId_(std::move(id)),
      fullName_(std::move(fullName)),
      email_(std::move(email)),
      departmentId_(std::move(deptId)),
      activeStatus_(active) {}

void User::deactivateUser() {
    activeStatus_ = false;
}

bool User::belongsToDepartment(const Department& department) const {
    const std::string& targetId = department.getDepartmentId();
    return departmentId_ == targetId;
}

bool User::validateEmailFormat() const {
    std::size_t atPos = email_.find('@');
    std::size_t dotPos = email_.find('.', atPos);
    return atPos != std::string::npos && dotPos != std::string::npos;
}

const std::string& User::getUserId() const {
    return userId_;
}

const std::string& User::getFullName() const {
    return fullName_;
}

bool User::isActive() const {
    return activeStatus_;
}

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
