#pragma once
#include <string>
#include "../ticketing/Invoice.h"
#include "../ticketing/PaymentTransaction.h"
#include "CateringOrder.h"

namespace airport {

class AirportFinance {
private:
    std::string fiscalPeriod_;
    double totalRevenueUsd_;
    double totalExpensesUsd_;
    double reserveFundUsd_;
    int processedInvoicesCount_;

public:
    AirportFinance(const std::string& fiscalPeriod,
                   double totalRevenueUsd,
                   double totalExpensesUsd,
                   double reserveFundUsd);

    void recordInvoiceRevenue(const Invoice& invoice, const PaymentTransaction& transaction);
    void payCateringExpense(const CateringOrder& order,
                            double standardPriceUsd,
                            double businessPriceUsd);
    double calculateNetProfitUsd() const;
    void allocateToReserve(double amountUsd);

    const std::string& getFiscalPeriod() const;
    double getTotalRevenueUsd() const;
    double getTotalExpensesUsd() const;
    double getReserveFundUsd() const;
    int getProcessedInvoicesCount() const;
};

}
