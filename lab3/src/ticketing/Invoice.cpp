#include "../../include/ticketing/Invoice.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kPercentDivisor = 100.0;
}

Invoice::Invoice(const std::string& invoiceId,
                 const Booking& booking,
                 double taxRatePercent)
    : invoiceId_(invoiceId),
      pnrCode_(booking.getPnrCode()),
      subtotalUsd_(booking.getTotalAmountUsd()),
      taxRatePercent_(taxRatePercent),
      isSettled_(false) {}

double Invoice::calculateTaxAmount() const {
    if (subtotalUsd_ <= 0.0 || taxRatePercent_ <= 0.0) {
        return 0.0;
    }
    return subtotalUsd_ * (taxRatePercent_ / kPercentDivisor);
}

double Invoice::calculateGrandTotal() const {
    return subtotalUsd_ + calculateTaxAmount();
}

void Invoice::settleInvoice(const PaymentTransaction& transaction) {
    if (!transaction.getIsSuccessful() || transaction.getPaidAmountUsd() < subtotalUsd_) {
        throw InsufficientFundsException("Transaction does not cover invoice subtotal");
    }
    isSettled_ = true;
}

const std::string& Invoice::getInvoiceId() const { return invoiceId_; }
const std::string& Invoice::getPnrCode() const { return pnrCode_; }
double Invoice::getSubtotalUsd() const { return subtotalUsd_; }
double Invoice::getTaxRatePercent() const { return taxRatePercent_; }
bool Invoice::getIsSettled() const { return isSettled_; }

}
