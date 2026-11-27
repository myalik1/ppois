#include <gtest/gtest.h>
#include "../../include/security/CustomsDeclaration.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(CustomsDeclarationTest, DutyCalculationAndInspection) {
    Passenger pax("PAX-5", "Ivan", 30, false);
    BaggageItem bag(20.0, 50.0, 40.0, 20.0, false);
    CustomsDeclaration decl("CUST-01", pax, 1500.0, false);

    EXPECT_TRUE(decl.requiresRedChannel(1000.0));
    EXPECT_DOUBLE_EQ(decl.calculateCustomsDutyUsd(1000.0, 15.0), 75.0);
    EXPECT_NO_THROW(decl.inspectAndApprove(bag, 30.0));
    EXPECT_TRUE(decl.getIsApproved());
    EXPECT_EQ(decl.getDeclarationId(), "CUST-01");
    EXPECT_EQ(decl.getPassengerId(), "PAX-5");
    EXPECT_DOUBLE_EQ(decl.getDeclaredGoodsValueUsd(), 1500.0);
    EXPECT_FALSE(decl.getCarriesRestrictedItems());

    CustomsDeclaration contraband("CUST-02", pax, 200.0, true);
    EXPECT_THROW(contraband.inspectAndApprove(bag, 30.0), SecurityBreachException);
}
