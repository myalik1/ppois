#pragma once

#include "../core/IdentityAndAccess.h"
#include "DocumentCore.h"
#include <string>

namespace docflow {

class ContractDocument {
public:
    ContractDocument(Document doc, std::string counterparty, double amount, int expirationDay);
    void prolongContract(int extraDays);
    bool isContractValidOnDay(int currentDay) const;
    int getExpirationDay() const;

private:
    Document baseDocument_;
    std::string counterpartyName_;
    double contractAmount_;
    int expirationDay_;
};

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

class OrderDocument {
public:
    OrderDocument(Document doc, std::string directive, std::string targetDeptId, int effectiveDay);
    bool isEffectiveOn(int currentDay) const;
    bool matchesTargetDepartment(const Department& department) const;

private:
    Document baseDocument_;
    std::string directiveText_;
    std::string targetDepartmentId_;
    int effectiveDay_;
};

class ReportDocument {
public:
    ReportDocument(Document doc, std::string period, int metricsCount, bool verified);
    void appendMetricSummary(const std::string& metricLine);
    void verifyReport(const User& reviewer);
    int getMetricsCount() const;
    bool isVerified() const;

private:
    Document baseDocument_;
    std::string reportingPeriod_;
    int metricsCount_;
    bool verifiedFlag_;
};

class MemoDocument {
public:
    MemoDocument(Document doc, std::string senderId, std::string recipientId, bool urgent);
    void escalateUrgency();
    bool isAddressedTo(const User& user) const;
    bool isUrgent() const;

private:
    Document baseDocument_;
    std::string senderUserId_;
    std::string recipientUserId_;
    bool urgentFlag_;
};

}
