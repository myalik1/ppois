#include "../../include/signatures/CryptoHasher.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

CryptoHasher::CryptoHasher(std::string algorithm, std::string saltPrefix, int iterations)
    : algorithmName_(std::move(algorithm)),
      saltPrefix_(std::move(saltPrefix)),
      iterationCount_(iterations) {}

std::string CryptoHasher::computeDigest(const std::string& payload) const {
    if (payload.empty()) {
        throw SignatureVerificationException("Cannot hash empty payload");
    }
    std::size_t rawHash = std::hash<std::string>{}(saltPrefix_ + payload);
    std::size_t mixedHash = rawHash ^ static_cast<std::size_t>(iterationCount_);
    return algorithmName_ + ":" + std::to_string(mixedHash);
}

bool CryptoHasher::verifyDigest(
    const std::string& payload, const std::string& expectedDigest) const {
    std::string actualDigest = computeDigest(payload);
    return actualDigest == expectedDigest;
}

}
