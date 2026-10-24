#pragma once

#include <string>

namespace docflow {

class DepartmentStats {
public:
    DepartmentStats(std::string departmentId, int createdCount, int archivedCount);
    void registerCreation();
    double calculateActiveRatio() const;

private:
    std::string departmentId_;
    int createdDocsCount_;
    int archivedDocsCount_;
};

}
