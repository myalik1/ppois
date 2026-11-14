#include "../../include/crew/MedicalCertificate.h"

namespace airport {

namespace {
const int kMinValidMedicalClass = 1;
const int kMaxValidMedicalClass = 2;
}

MedicalCertificate::MedicalCertificate(const std::string& certificateId,
                                       int medicalClass,
                                       int expiryYear,
                                       bool isFitForDuty)
    : certificateId_(certificateId),
      medicalClass_(medicalClass),
      expiryYear_(expiryYear),
      isFitForDuty_(isFitForDuty) {}

bool MedicalCertificate::validateMedicalFitness(int currentYear) const {
    bool validClass = medicalClass_ >= kMinValidMedicalClass &&
                      medicalClass_ <= kMaxValidMedicalClass;
    return isFitForDuty_ && validClass && currentYear <= expiryYear_;
}

void MedicalCertificate::suspendCertificate() {
    isFitForDuty_ = false;
}

void MedicalCertificate::voidextendValidity(int yearsToAdd) {
    if (yearsToAdd > 0) {
        expiryYear_ += yearsToAdd;
        isFitForDuty_ = true;
    }
}

const std::string& MedicalCertificate::getCertificateId() const { return certificateId_; }
int MedicalCertificate::getMedicalClass() const { return medicalClass_; }
int MedicalCertificate::getExpiryYear() const { return expiryYear_; }
bool MedicalCertificate::getIsFitForDuty() const { return isFitForDuty_; }

}
