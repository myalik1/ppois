#pragma once

#include <string>

namespace docflow {

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

}
