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

class StorageCapacityExceededException : public DocumentWorkflowException {
public:
    explicit StorageCapacityExceededException(const std::string& message);
};

class InvalidDocumentDataException : public DocumentWorkflowException {
public:
    explicit InvalidDocumentDataException(const std::string& message);
};

}
