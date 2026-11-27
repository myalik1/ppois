#include <gtest/gtest.h>
#include "../../include/ticketing/PaymentTransaction.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(PaymentTransactionTest, ProcessAndRefundPayment) {
    Passenger pax("PAX-1", "Ivan", 25, false);
    Booking booking("PNR-1", pax);
    Ticket ticket("TKT-1", "B2-1", 150.0, true);
    booking.addTicketToBooking(ticket);

    PaymentTransaction poorTx("TX-01", "CARD", 50.0);
    EXPECT_THROW(poorTx.processPayment(booking), InsufficientFundsException);

    PaymentTransaction validTx("TX-02", "CARD", 300.0);
    EXPECT_TRUE(validTx.verifyTransactionIntegrity());
    EXPECT_NO_THROW(validTx.processPayment(booking));
    EXPECT_TRUE(validTx.getIsSuccessful());
    EXPECT_DOUBLE_EQ(validTx.getPaidAmountUsd(), 150.0);
    EXPECT_DOUBLE_EQ(validTx.getCustomerBalanceUsd(), 150.0);

    validTx.refundPayment(booking);
    EXPECT_FALSE(validTx.getIsSuccessful());
    EXPECT_DOUBLE_EQ(validTx.getCustomerBalanceUsd(), 300.0);
    EXPECT_EQ(validTx.getTransactionId(), "TX-02");
    EXPECT_EQ(validTx.getPaymentMethod(), "CARD");
}
