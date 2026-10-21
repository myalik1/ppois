#include "../../include/documents/SpecializedDocuments.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const double kPercentDivisor = 100.0;
const double kAmountTolerance = 0.01;
}

ContractDocument::ContractDocument(
    Document doc, std::string counterparty, double amount, int expirationDay)
    : baseDocument_(std::move(doc)),
      counterpartyName_(std::move(counterparty)),
      contractAmount_(amount),
      expirationDay_(expirationDay) {}

void ContractDocument::prolongContract(int extraDays) {
    if (extraDays <= 0) {
        throw InvalidDocumentDataException("Extension days must be positive");
    }
    expirationDay_ += extraDays;
}

bool ContractDocument::isContractValidOnDay(int currentDay) const {
    return currentDay <= expirationDay_ && contractAmount_ > 0.0;
}

int ContractDocument::getExpirationDay() const {
    return expirationDay_;
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

OrderDocument::OrderDocument(
    Document doc, std::string directive, std::string targetDeptId, int effectiveDay)
    : baseDocument_(std::move(doc)),
      directiveText_(std::move(directive)),
      targetDepartmentId_(std::move(targetDeptId)),
      effectiveDay_(effectiveDay) {}

bool OrderDocument::isEffectiveOn(int currentDay) const {
    return currentDay >= effectiveDay_ && !directiveText_.empty();
}

bool OrderDocument::matchesTargetDepartment(const Department& department) const {
    const std::string& deptId = department.getDepartmentId();
    return targetDepartmentId_ == deptId;
}

ReportDocument::ReportDocument(Document doc, std::string period, int metricsCount, bool verified)
    : baseDocument_(std::move(doc)),
      reportingPeriod_(std::move(period)),
      metricsCount_(metricsCount),
      verifiedFlag_(verified) {}

void ReportDocument::appendMetricSummary(const std::string& metricLine) {
    if (metricLine.empty()) {
        throw InvalidDocumentDataException("Metric summary cannot be empty");
    }
    metricsCount_ += 1;
}

void ReportDocument::verifyReport(const User& reviewer) {
    if (!reviewer.isActive()) {
        throw UnauthorizedAccessException("Inactive reviewer cannot verify report");
    }
    verifiedFlag_ = true;
    baseDocument_.transitionStatus("VERIFIED");
}

int ReportDocument::getMetricsCount() const {
    return metricsCount_;
}

bool ReportDocument::isVerified() const {
    return verifiedFlag_;
}

MemoDocument::MemoDocument(Document doc, std::string senderId, std::string recipientId, bool urgent)
    : baseDocument_(std::move(doc)),
      senderUserId_(std::move(senderId)),
      recipientUserId_(std::move(recipientId)),
      urgentFlag_(urgent) {}

void MemoDocument::escalateUrgency() {
    urgentFlag_ = true;
}

bool MemoDocument::isAddressedTo(const User& user) const {
    const std::string& targetId = user.getUserId();
    return recipientUserId_ == targetId;
}

bool MemoDocument::isUrgent() const {
    return urgentFlag_;
}

}
