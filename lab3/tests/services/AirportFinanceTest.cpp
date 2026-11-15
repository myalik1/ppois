#include <gtest/gtest.h>
#include "../../include/services/AirportFinance.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(AirportFinanceTest, RevenueExpenseAndProfit) {
    AirportFinance finance("2026-Q2", 5000.0, 1000.0, 2000.0);
    Passenger pax("PAX-1", "Ivan", 25, false);
    Booking booking("PNR-1", pax);
    Ticket ticket("TKT-1", "B2-1", 200.0, true);
    booking.addTicketToBooking(ticket);
    PaymentTransaction tx("TX-1", "CARD", 500.0);
    tx.processPayment(booking);
    Invoice invoice("INV-1", booking, 10.0);
    invoice.settleInvoice(tx);

    EXPECT_NO_THROW(finance.recordInvoiceRevenue(invoice, tx));
    EXPECT_DOUBLE_EQ(finance.getTotalRevenueUsd(), 5220.0);
    EXPECT_EQ(finance.getProcessedInvoicesCount(), 1);

    Flight flight("B2-1", 100, 600);
    CateringOrder order("CAT-1", flight, 50, 10);
    EXPECT_NO_THROW(finance.payCateringExpense(order, 10.0, 20.0));
    EXPECT_DOUBLE_EQ(finance.getTotalExpensesUsd(), 1700.0);
    EXPECT_DOUBLE_EQ(finance.calculateNetProfitUsd(), 3520.0);

    finance.allocateToReserve(520.0);
    EXPECT_DOUBLE_EQ(finance.getReserveFundUsd(), 2520.0);
    EXPECT_EQ(finance.getFiscalPeriod(), "2026-Q2");
}
