#include "../include/exceptions/WorkflowExceptions.h"
#include "../include/core/User.h"
#include "../include/documents/Document.h"
#include "../include/documents/DocumentMetadata.h"
#include "../include/workflow/ApprovalRoute.h"
#include "../include/workflow/ApprovalStep.h"
#include "../include/workflow/EscalationRule.h"
#include "../include/workflow/WorkflowManager.h"
#include "../include/workflow/WorkflowState.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(WorkflowEngineTest, FullApprovalLifecycleAndEscalation) {
    User firstApprover("U1", "Boss 1", "b1@b.c", "D1", true);
    User secondApprover("U2", "Boss 2", "b2@b.c", "D1", true);
    Document doc("DOC-10", "Budget", "U0", DocumentMetadata(1, 1, "RU", 2));

    ApprovalRoute route("R1", "TwoStepRoute");
    route.appendStep(ApprovalStep(1, "U1"));
    route.appendStep(ApprovalStep(2, "U2"));

    WorkflowManager manager("WM-1");
    manager.startWorkflow(doc, route);
    EXPECT_EQ(doc.getStatus(), "IN_REVIEW");

    EscalationRule escRule("ESC-1", 24, "U-BACKUP");
    EXPECT_EQ(manager.applyEscalation("DOC-10", escRule), "U1");

    manager.submitApproval(doc, firstApprover, "Step 1 OK");
    EXPECT_EQ(doc.getStatus(), "IN_REVIEW");

    manager.submitApproval(doc, secondApprover, "Step 2 OK");
    EXPECT_EQ(doc.getStatus(), "APPROVED");
    EXPECT_EQ(manager.getState("DOC-10").getStageName(), "APPROVED");
}

TEST(WorkflowEngineTest, ApprovalStepExceptionsAndGetters) {
    ApprovalStep step(1, "U1");
    User wrongUser("U2", "Wrong", "w@b.c", "D1", true);
    User inactiveUser("U1", "Inactive", "i@b.c", "D1", false);

    EXPECT_THROW(step.approveStep(wrongUser, "OK"), UnauthorizedAccessException);
    EXPECT_THROW(step.approveStep(inactiveUser, "OK"), UnauthorizedAccessException);
    EXPECT_THROW(step.rejectStep(wrongUser, "No"), WorkflowRouteException);
    EXPECT_THROW(step.rejectStep(User("U1", "", "", "", true), ""), WorkflowRouteException);
}

TEST(WorkflowEngineTest, WorkflowStateExceptionsAndBlocked) {
    WorkflowState state("DOC-1", "DRAFT", 10, true); // Заблокировано
    EXPECT_TRUE(state.isBlocked());
    EXPECT_THROW(state.advanceHours(5), InvalidDocumentStateException);
    EXPECT_THROW(state.moveToStage("NEXT"), InvalidDocumentStateException);

    WorkflowState activeState("DOC-2", "DRAFT", 0, false);
    EXPECT_THROW(activeState.advanceHours(-5), InvalidDocumentStateException);
    EXPECT_THROW(activeState.moveToStage(""), InvalidDocumentStateException);
}

TEST(WorkflowEngineTest, WorkflowManagerExceptions) {
    WorkflowManager manager("WM-2");
    Document doc("DOC-X", "Title", "U1", DocumentMetadata(1, 1, "RU", 1));
    User user("U1", "Name", "e@b.c", "D1", true);

    EXPECT_THROW(manager.submitApproval(doc, user, "C"), WorkflowRouteException);
    EXPECT_THROW(manager.getState("DOC-MISSING"), DocumentNotFoundException);

    EscalationRule rule("R1", 10, "U2");
    EXPECT_THROW(manager.applyEscalation("DOC-MISSING", rule), WorkflowRouteException);
}
