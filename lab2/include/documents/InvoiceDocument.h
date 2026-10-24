#pragma once

#include "Document.h"
#include <string>

namespace docflow {

class InvoiceDocument {
public:
    InvoiceDocument(Document doc, double netAmount, double taxRatePercent, bool paid);
    double calculateGrossTotal() const;
    void markAsPaid(double paidAmount);
    bool isPaid() const;

private:
    Document baseDocument_;
    double netAmount_;
    double taxRatePercent_;
    bool paidStatus_;
};

}
