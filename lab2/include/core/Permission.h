#pragma once

#include <string>

namespace docflow {

class Permission {
public:
    Permission(std::string code, std::string resource, int level);
    bool grantsLevel(int requiredLevel) const;
    bool matchesResource(const std::string& resource) const;
    const std::string& getPermissionCode() const;

private:
    std::string permissionCode_;
    std::string resourceName_;
    int accessLevel_;
};

}
