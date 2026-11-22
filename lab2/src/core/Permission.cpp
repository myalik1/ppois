#include "../../include/core/Permission.h"

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

}
