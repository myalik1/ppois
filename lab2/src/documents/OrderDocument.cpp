#include "../../include/documents/OrderDocument.h"

namespace docflow {

OrderDocument::OrderDocument(
    Document doc, std::string directive, std::string targetDeptId, int effectiveDay)
    : baseDocument_(std::move(doc)),
      directiveText_(std::move(directive)),
      targetDepartmentId_(std::move(targetDeptId)),
      effectiveDay_(effectiveDay) {}

bool OrderDocument::isEffectiveOn(int currentDay) const {
    return currentDay >= effectiveDay_ && !directiveText_.empty();
}

bool OrderDocument::matchesTargetDepartment(const Department& department) const {
    const std::string& deptId = department.getDepartmentId();
    return targetDepartmentId_ == deptId;
}

}
