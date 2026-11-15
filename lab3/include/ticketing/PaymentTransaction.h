#pragma once
#include <string>
#include "Booking.h"

namespace airport {

class PaymentTransaction {
private:
    std::string transactionId_;
    std::string paymentMethod_;
    double paidAmountUsd_;
    double customerBalanceUsd_;
    bool isSuccessful_;

public:
    PaymentTransaction(const std::string& transactionId,
                       const std::string& paymentMethod,
                       double customerBalanceUsd);

    void processPayment(Booking& booking);
    void refundPayment(Booking& booking);
    bool verifyTransactionIntegrity() const;

    const std::string& getTransactionId() const;
    const std::string& getPaymentMethod() const;
    double getPaidAmountUsd() const;
    double getCustomerBalanceUsd() const;
    bool getIsSuccessful() const;
};

}
