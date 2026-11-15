#include <gtest/gtest.h>
#include "../../include/passengers/Passenger.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(PassengerTest, CheckInDocumentsAndBaggageWeight) {
    Passenger passenger("PAX-01", "Kirill Myalik", 20, false);
    Passport passport("MP7654321", "Kirill Myalik", "BLR", 2021, 2031);
    Visa visa("V-112233", "DEU", 2028, 90, true);
    LoyaltyCard card("LC-777", 10000, "BRONZE", true);
    BaggageItem checked(20.0, 50.0, 40.0, 20.0, false);
    HandLuggage cabin(5.5, false, 0, true);

    EXPECT_NO_THROW(passenger.verifyTravelDocuments(passport, visa, 2026));
    EXPECT_NO_THROW(passenger.completeCheckIn(passport, 2026));
    EXPECT_TRUE(passenger.getIsCheckedIn());

    passenger.addLoyaltyPoints(card, 5000);
    EXPECT_EQ(card.getMilesBalance(), 15000);
    EXPECT_DOUBLE_EQ(passenger.calculateTotalBaggageWeight(checked, cabin), 25.5);
    EXPECT_EQ(passenger.getPassengerId(), "PAX-01");
    EXPECT_EQ(passenger.getFullName(), "Kirill Myalik");
    EXPECT_EQ(passenger.getAge(), 20);
    EXPECT_FALSE(passenger.getHasSpecialAssistance());
}

TEST(PassengerTest, MismatchedPassportNameThrows) {
    Passenger passenger("PAX-02", "Kirill Myalik", 20, false);
    Passport wrongPass("MP7654321", "Other Person", "BLR", 2021, 2031);
    Visa visa("V-112233", "DEU", 2028, 90, true);

    EXPECT_THROW(passenger.verifyTravelDocuments(wrongPass, visa, 2026), InvalidPassportException);
}
