#include "../../include/documents/ContractDocument.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

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

}
