#pragma once

#include "Document.h"
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

}
