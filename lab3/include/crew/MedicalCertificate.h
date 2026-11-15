#pragma once
#include <string>

namespace airport {

class MedicalCertificate {
private:
    std::string certificateId_;
    int medicalClass_;
    int expiryYear_;
    bool isFitForDuty_;

public:
    MedicalCertificate(const std::string& certificateId,
                       int medicalClass,
                       int expiryYear,
                       bool isFitForDuty = true);

    bool validateMedicalFitness(int currentYear) const;
    void suspendCertificate();
    void voidextendValidity(int yearsToAdd);

    const std::string& getCertificateId() const;
    int getMedicalClass() const;
    int getExpiryYear() const;
    bool getIsFitForDuty() const;
};

}
