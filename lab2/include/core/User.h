#pragma once

#include "Department.h"
#include <string>

namespace docflow {

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

}
