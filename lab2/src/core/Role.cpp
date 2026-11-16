#include "../../include/core/Role.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

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

}
