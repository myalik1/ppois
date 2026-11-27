#pragma once

#include <string>

namespace airport {

class Passport {
private:
    std::string passportNumber_;
    std::string holderFullName_;
    std::string nationality_;
    int issueYear_;
    int expiryYear_;

public:
    Passport(const std::string& passportNumber,
             const std::string& holderFullName,
             const std::string& nationality,
             int issueYear,
             int expiryYear);

    bool isValidForYear(int currentYear) const;
    void verifyFormat() const;
    int remainingValidityYears(int currentYear) const;

    const std::string& getPassportNumber() const;
    const std::string& getHolderFullName() const;
    const std::string& getNationality() const;
    int getIssueYear() const;
    int getExpiryYear() const;
};

}
