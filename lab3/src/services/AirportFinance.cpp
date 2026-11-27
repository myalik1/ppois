#include "../../include/services/AirportFinance.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

AirportFinance::AirportFinance(const std::string& fiscalPeriod,
                               double totalRevenueUsd,
                               double totalExpensesUsd,
                               double reserveFundUsd)
    : fiscalPeriod_(fiscalPeriod),
      totalRevenueUsd_(totalRevenueUsd),
      totalExpensesUsd_(totalExpensesUsd),
      reserveFundUsd_(reserveFundUsd),
      processedInvoicesCount_(0) {}

void AirportFinance::recordInvoiceRevenue(const Invoice& invoice,
                                          const PaymentTransaction& transaction) {
    if (!invoice.getIsSettled() || !transaction.getIsSuccessful()) {
        throw InsufficientFundsException("Cannot record unsettled invoice revenue");
    }
    totalRevenueUsd_ += invoice.calculateGrandTotal();
    ++processedInvoicesCount_;
}

void AirportFinance::payCateringExpense(const CateringOrder& order,
                                        double standardPriceUsd,
                                        double businessPriceUsd) {
    double cost = order.calculateTotalCateringCost(standardPriceUsd, businessPriceUsd);
    if (cost > totalRevenueUsd_ + reserveFundUsd_) {
        throw InsufficientFundsException("Airport lacks funds to cover catering expense");
    }
    totalExpensesUsd_ += cost;
}

double AirportFinance::calculateNetProfitUsd() const {
    return totalRevenueUsd_ - totalExpensesUsd_;
}

void AirportFinance::allocateToReserve(double amountUsd) {
    if (amountUsd > 0.0 && amountUsd <= calculateNetProfitUsd()) {
        reserveFundUsd_ += amountUsd;
        totalExpensesUsd_ += amountUsd;
    }
}

const std::string& AirportFinance::getFiscalPeriod() const { return fiscalPeriod_; }
double AirportFinance::getTotalRevenueUsd() const { return totalRevenueUsd_; }
double AirportFinance::getTotalExpensesUsd() const { return totalExpensesUsd_; }
double AirportFinance::getReserveFundUsd() const { return reserveFundUsd_; }
int AirportFinance::getProcessedInvoicesCount() const { return processedInvoicesCount_; }

}
