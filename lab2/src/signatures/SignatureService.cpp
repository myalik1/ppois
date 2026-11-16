#include "../../include/signatures/SignatureService.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

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
