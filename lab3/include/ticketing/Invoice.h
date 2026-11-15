#pragma once
#include <string>
#include "Booking.h"
#include "PaymentTransaction.h"

namespace airport {

class Invoice {
private:
    std::string invoiceId_;
    std::string pnrCode_;
    double subtotalUsd_;
    double taxRatePercent_;
    bool isSettled_;

public:
    Invoice(const std::string& invoiceId,
            const Booking& booking,
            double taxRatePercent);

    double calculateTaxAmount() const;
    double calculateGrandTotal() const;
    void settleInvoice(const PaymentTransaction& transaction);

    const std::string& getInvoiceId() const;
    const std::string& getPnrCode() const;
    double getSubtotalUsd() const;
    double getTaxRatePercent() const;
    bool getIsSettled() const;
};

}
