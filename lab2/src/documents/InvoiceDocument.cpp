#include "../../include/documents/InvoiceDocument.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const double kPercentDivisor = 100.0;
const double kAmountTolerance = 0.01;
}

InvoiceDocument::InvoiceDocument(Document doc, double netAmount, double taxRatePercent, bool paid)
    : baseDocument_(std::move(doc)),
      netAmount_(netAmount),
      taxRatePercent_(taxRatePercent),
      paidStatus_(paid) {}

double InvoiceDocument::calculateGrossTotal() const {
    double taxFraction = taxRatePercent_ / kPercentDivisor;
    return netAmount_ * (1.0 + taxFraction);
}

void InvoiceDocument::markAsPaid(double paidAmount) {
    double requiredTotal = calculateGrossTotal();
    if (paidAmount + kAmountTolerance < requiredTotal) {
        throw InvalidDocumentDataException("Paid amount is less than invoice gross total");
    }
    paidStatus_ = true;
    baseDocument_.transitionStatus("PAID");
}

bool InvoiceDocument::isPaid() const {
    return paidStatus_;
}

}
