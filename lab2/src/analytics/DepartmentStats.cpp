#include "../../include/analytics/DepartmentStats.h"

namespace docflow {

DepartmentStats::DepartmentStats(std::string departmentId, int createdCount, int archivedCount)
    : departmentId_(std::move(departmentId)),
      createdDocsCount_(createdCount),
      archivedDocsCount_(archivedCount) {}

void DepartmentStats::registerCreation() {
    createdDocsCount_ += 1;
}

double DepartmentStats::calculateActiveRatio() const {
    if (createdDocsCount_ <= 0) {
        return 0.0;
    }
    int activeCount = createdDocsCount_ - archivedDocsCount_;
    return static_cast<double>(activeCount) / static_cast<double>(createdDocsCount_);
}

}
