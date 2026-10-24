#pragma once

#include "../core/Department.h"
#include "Document.h"
#include <string>

namespace docflow {

class OrderDocument {
public:
    OrderDocument(Document doc, std::string directive, std::string targetDeptId, int effectiveDay);
    bool isEffectiveOn(int currentDay) const;
    bool matchesTargetDepartment(const Department& department) const;

private:
    Document baseDocument_;
    std::string directiveText_;
    std::string targetDepartmentId_;
    int effectiveDay_;
};

}
