#pragma once

#include "Role.h"
#include "User.h"
#include <map>
#include <string>

namespace docflow {

class AccessController {
public:
    AccessController(std::string controllerId, bool strictMode);
    void assignRole(const User& user, const Role& role);
    bool verifyAccess(const User& user, const std::string& resource, int level) const;
    void revokeUserAccess(const std::string& userId);

private:
    std::string controllerId_;
    bool strictMode_;
    std::map<std::string, Role> assignedRoles_;
};

}
