#pragma once

#include <map>
#include <string>
#include <vector>

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

class Department {
public:
    Department(std::string id, std::string name, std::string headUserId, int monthlyQuota);
    void consumeQuota(int documentCount);
    bool isHead(const std::string& userId) const;
    const std::string& getDepartmentId() const;
    const std::string& getDepartmentName() const;
    int getMonthlyQuota() const;

private:
    std::string departmentId_;
    std::string departmentName_;
    std::string headUserId_;
    int monthlyQuota_;
};

class User {
public:
    User(std::string id, std::string fullName, std::string email, std::string deptId, bool active);
    void deactivateUser();
    bool belongsToDepartment(const Department& department) const;
    bool validateEmailFormat() const;
    const std::string& getUserId() const;
    const std::string& getFullName() const;
    bool isActive() const;

private:
    std::string userId_;
    std::string fullName_;
    std::string email_;
    std::string departmentId_;
    bool activeStatus_;
};

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
