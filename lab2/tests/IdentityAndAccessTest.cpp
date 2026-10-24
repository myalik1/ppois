#include "../include/core/IdentityAndAccess.h"
#include "../include/exceptions/WorkflowExceptions.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(IdentityAndAccessTest, PermissionAndRoleAccessVerification) {
    Permission readPerm("P1", "DOCUMENT", 3);
    EXPECT_TRUE(readPerm.grantsLevel(2));
    EXPECT_FALSE(readPerm.grantsLevel(5));
    EXPECT_TRUE(readPerm.matchesResource("DOCUMENT"));

    Role editor("Editor", 5);
    Role viewer("Viewer", 1);
    editor.addPermission(readPerm);
    EXPECT_TRUE(editor.hasResourceAccess("DOCUMENT", 2));
    EXPECT_FALSE(editor.hasResourceAccess("ARCHIVE", 1));
    EXPECT_TRUE(editor.canOverrideRole(viewer));
    EXPECT_THROW(editor.addPermission(Permission("", "DOC", 1)), InvalidDocumentDataException);
}

TEST(IdentityAndAccessTest, DepartmentUserAndAccessControllerLogic) {
    Department dept("D1", "Legal", "U1", 10);
    dept.consumeQuota(4);
    EXPECT_EQ(dept.getMonthlyQuota(), 6);
    EXPECT_TRUE(dept.isHead("U1"));
    EXPECT_THROW(dept.consumeQuota(20), StorageCapacityExceededException);

    User user("U1", "Ivan Ivanov", "ivan@company.by", "D1", true);
    EXPECT_TRUE(user.belongsToDepartment(dept));
    EXPECT_TRUE(user.validateEmailFormat());

    Role manager("Manager", 10);
    manager.addPermission(Permission("P2", "DOCUMENT", 4));

    AccessController controller("AC1", true);
    controller.assignRole(user, manager);
    EXPECT_TRUE(controller.verifyAccess(user, "DOCUMENT", 3));
    controller.revokeUserAccess("U1");
    EXPECT_THROW(controller.verifyAccess(user, "DOCUMENT", 1), UnauthorizedAccessException);

    user.deactivateUser();
    EXPECT_FALSE(user.isActive());
    EXPECT_THROW(controller.assignRole(user, manager), UnauthorizedAccessException);
}
