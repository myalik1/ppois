#include "../../include/core/Department.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

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

}
