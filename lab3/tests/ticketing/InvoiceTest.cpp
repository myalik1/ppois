#include <gtest/gtest.h>
#include "../../include/ticketing/Invoice.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(InvoiceTest, TaxTotalAndSettlement) {
    Passenger pax("PAX-1", "Ivan", 25, false);
    Booking booking("PNR-99", pax);
    Ticket ticket("TKT-1", "B2-1", 100.0, true);
    booking.addTicketToBooking(ticket);

    Invoice invoice("INV-10", booking, 20.0);
    EXPECT_DOUBLE_EQ(invoice.calculateTaxAmount(), 20.0);
    EXPECT_DOUBLE_EQ(invoice.calculateGrandTotal(), 120.0);

    PaymentTransaction tx("TX-10", "CARD", 200.0);
    EXPECT_THROW(invoice.settleInvoice(tx), InsufficientFundsException);

    tx.processPayment(booking);
    EXPECT_NO_THROW(invoice.settleInvoice(tx));
    EXPECT_TRUE(invoice.getIsSettled());
    EXPECT_EQ(invoice.getInvoiceId(), "INV-10");
    EXPECT_EQ(invoice.getPnrCode(), "PNR-99");
    EXPECT_DOUBLE_EQ(invoice.getSubtotalUsd(), 100.0);
    EXPECT_DOUBLE_EQ(invoice.getTaxRatePercent(), 20.0);
}
