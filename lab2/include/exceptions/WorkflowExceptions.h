#pragma once

#include <stdexcept>
#include <string>

namespace docflow {

class DocumentWorkflowException : public std::runtime_error {
public:
    explicit DocumentWorkflowException(const std::string& message, int errorCode = 1000);
    int getErrorCode() const noexcept;

private:
    int errorCode_;
};

class InvalidDocumentStateException : public DocumentWorkflowException {
public:
    explicit InvalidDocumentStateException(const std::string& message);
};

class UnauthorizedAccessException : public DocumentWorkflowException {
public:
    explicit UnauthorizedAccessException(const std::string& message);
};

class DocumentNotFoundException : public DocumentWorkflowException {
public:
    explicit DocumentNotFoundException(const std::string& message);
};

class SignatureVerificationException : public DocumentWorkflowException {
public:
    explicit SignatureVerificationException(const std::string& message);
};

class CertificateExpiredException : public DocumentWorkflowException {
public:
    explicit CertificateExpiredException(const std::string& message);
};

class WorkflowRouteException : public DocumentWorkflowException {
public:
    explicit WorkflowRouteException(const std::string& message);
};

class StorageCapacityExceededException : public DocumentWorkflowException {
public:
    explicit StorageCapacityExceededException(const std::string& message);
};

class ArchivePolicyViolationException : public DocumentWorkflowException {
public:
    explicit ArchivePolicyViolationException(const std::string& message);
};

class InvalidDocumentDataException : public DocumentWorkflowException {
public:
    explicit InvalidDocumentDataException(const std::string& message);
};

}
