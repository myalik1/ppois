#include "../../include/core/User.h"

namespace docflow {

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

}
