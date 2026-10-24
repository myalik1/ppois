#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const int kInvalidStateCode = 1001;
const int kUnauthorizedCode = 1002;
const int kNotFoundCode = 1003;
const int kSignatureErrorCode = 1004;
const int kCertExpiredCode = 1005;
const int kWorkflowRouteCode = 1006;
const int kStorageCapacityCode = 1007;
const int kArchivePolicyCode = 1008;
const int kInvalidDataCode = 1009;
const int kComplianceCode = 1010;
const int kSlaBreachCode = 1011;
}

DocumentWorkflowException::DocumentWorkflowException(const std::string& message, int errorCode)
    : std::runtime_error(message), errorCode_(errorCode) {}

int DocumentWorkflowException::getErrorCode() const noexcept {
    return errorCode_;
}

InvalidDocumentStateException::InvalidDocumentStateException(const std::string& message)
    : DocumentWorkflowException(message, kInvalidStateCode) {}

UnauthorizedAccessException::UnauthorizedAccessException(const std::string& message)
    : DocumentWorkflowException(message, kUnauthorizedCode) {}

DocumentNotFoundException::DocumentNotFoundException(const std::string& message)
    : DocumentWorkflowException(message, kNotFoundCode) {}

SignatureVerificationException::SignatureVerificationException(const std::string& message)
    : DocumentWorkflowException(message, kSignatureErrorCode) {}

CertificateExpiredException::CertificateExpiredException(const std::string& message)
    : DocumentWorkflowException(message, kCertExpiredCode) {}

WorkflowRouteException::WorkflowRouteException(const std::string& message)
    : DocumentWorkflowException(message, kWorkflowRouteCode) {}

StorageCapacityExceededException::StorageCapacityExceededException(const std::string& message)
    : DocumentWorkflowException(message, kStorageCapacityCode) {}

ArchivePolicyViolationException::ArchivePolicyViolationException(const std::string& message)
    : DocumentWorkflowException(message, kArchivePolicyCode) {}

InvalidDocumentDataException::InvalidDocumentDataException(const std::string& message)
    : DocumentWorkflowException(message, kInvalidDataCode) {}

ComplianceViolationException::ComplianceViolationException(const std::string& message)
    : DocumentWorkflowException(message, kComplianceCode) {}

SlaBreachException::SlaBreachException(const std::string& message)
    : DocumentWorkflowException(message, kSlaBreachCode) {}

}
