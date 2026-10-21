#include "../../include/signatures/DigitalSignatures.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const std::size_t kMinHashLength = 6;
}

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

Certificate::Certificate(
    std::string serial, std::string holderUserId, std::string issuer, int validUntil, bool revoked)
    : serialNumber_(std::move(serial)),
      holderUserId_(std::move(holderUserId)),
      issuerName_(std::move(issuer)),
      validUntilDay_(validUntil),
      revokedFlag_(revoked) {}

void Certificate::revokeCertificate() {
    revokedFlag_ = true;
}

bool Certificate::isValidForUser(const User& user, int currentDay) const {
    if (revokedFlag_ || currentDay > validUntilDay_) {
        return false;
    }
    const std::string& uid = user.getUserId();
    return holderUserId_ == uid;
}

const std::string& Certificate::getSerialNumber() const {
    return serialNumber_;
}

DigitalSignature::DigitalSignature(
    std::string sigId, std::string docId, std::string certSerial, std::string sigHash)
    : signatureId_(std::move(sigId)),
      documentId_(std::move(docId)),
      signerCertSerial_(std::move(certSerial)),
      signatureHash_(std::move(sigHash)) {}

bool DigitalSignature::matchesDocument(const Document& document) const {
    const std::string& docId = document.getDocumentId();
    return documentId_ == docId;
}

bool DigitalSignature::validateHashFormat() const {
    return signatureHash_.size() >= kMinHashLength &&
           signatureHash_.find(':') != std::string::npos;
}

const std::string& DigitalSignature::getSignatureHash() const {
    return signatureHash_;
}

OfficialStamp::OfficialStamp(std::string code, std::string orgName, std::string regNumber)
    : stampCode_(std::move(code)),
      organizationName_(std::move(orgName)),
      registrationNumber_(std::move(regNumber)) {}

std::string OfficialStamp::formatStampMark() const {
    return "[" + stampCode_ + "|" + organizationName_ + "|" + registrationNumber_ + "]";
}

bool OfficialStamp::belongsToOrganization(const std::string& orgName) const {
    return organizationName_ == orgName;
}

SignatureService::SignatureService(std::string serviceName, CryptoHasher hasher)
    : serviceName_(std::move(serviceName)), hasher_(std::move(hasher)) {}

DigitalSignature SignatureService::signDocument(
    const Document& document, const User& signer, const Certificate& cert, int currentDay) {
    if (!cert.isValidForUser(signer, currentDay)) {
        throw CertificateExpiredException("Certificate is expired, revoked, or mismatched");
    }
    const std::string& docId = document.getDocumentId();
    std::string payload = docId + ":" + document.getTitle();
    std::string digest = hasher_.computeDigest(payload);
    std::string sigId = "SIG-" + docId + "-" + signer.getUserId();
    DigitalSignature signature(sigId, docId, cert.getSerialNumber(), digest);
    signaturesByDoc_[docId].push_back(signature);
    return signature;
}

bool SignatureService::verifyDocumentSignatures(
    const Document& document, const Certificate& cert, int currentDay) const {
    if (currentDay <= 0 || cert.getSerialNumber().empty()) {
        throw SignatureVerificationException("Invalid parameters for signature verification");
    }
    const std::string& docId = document.getDocumentId();
    auto it = signaturesByDoc_.find(docId);
    if (it == signaturesByDoc_.end() || it->second.empty()) {
        return false;
    }
    std::string payload = docId + ":" + document.getTitle();
    for (const auto& sig : it->second) {
        if (!hasher_.verifyDigest(payload, sig.getSignatureHash())) {
            throw SignatureVerificationException("Signature digest mismatch detected");
        }
    }
    return true;
}

std::size_t SignatureService::countSignatures(const std::string& documentId) const {
    auto it = signaturesByDoc_.find(documentId);
    if (it == signaturesByDoc_.end()) {
        return 0;
    }
    return it->second.size();
}

}
