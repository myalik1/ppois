#pragma once

#include "Permission.h"
#include <string>
#include <vector>

namespace docflow {

class Role {
public:
    Role() = default;
    Role(std::string name, int priorityRank);
    void addPermission(const Permission& permission);
    bool hasResourceAccess(const std::string& resource, int level) const;
    bool canOverrideRole(const Role& otherRole) const;
    const std::string& getRoleName() const;

private:
    std::string roleName_;
    int priorityRank_{0};
    std::vector<Permission> permissions_;
};

}
