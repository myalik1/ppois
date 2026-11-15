#include "../../include/ticketing/PaymentTransaction.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

PaymentTransaction::PaymentTransaction(const std::string& transactionId,
                                       const std::string& paymentMethod,
                                       double customerBalanceUsd)
    : transactionId_(transactionId),
      paymentMethod_(paymentMethod),
      paidAmountUsd_(0.0),
      customerBalanceUsd_(customerBalanceUsd),
      isSuccessful_(false) {}

void PaymentTransaction::processPayment(Booking& booking) {
    double required = booking.getTotalAmountUsd();
    if (required <= 0.0) {
        throw InvalidTicketException("Booking total must be positive");
    }
    if (customerBalanceUsd_ < required) {
        throw InsufficientFundsException("Customer balance is insufficient for booking");
    }
    customerBalanceUsd_ -= required;
    paidAmountUsd_ = required;
    isSuccessful_ = true;
    booking.confirmBooking();
}

void PaymentTransaction::refundPayment(Booking& booking) {
    if (isSuccessful_) {
        customerBalanceUsd_ += paidAmountUsd_;
        paidAmountUsd_ = 0.0;
        isSuccessful_ = false;
        booking.cancelBooking();
    }
}

bool PaymentTransaction::verifyTransactionIntegrity() const {
    return !transactionId_.empty() && !paymentMethod_.empty() && customerBalanceUsd_ >= 0.0;
}

const std::string& PaymentTransaction::getTransactionId() const { return transactionId_; }
const std::string& PaymentTransaction::getPaymentMethod() const { return paymentMethod_; }
double PaymentTransaction::getPaidAmountUsd() const { return paidAmountUsd_; }
double PaymentTransaction::getCustomerBalanceUsd() const { return customerBalanceUsd_; }
bool PaymentTransaction::getIsSuccessful() const { return isSuccessful_; }

}
