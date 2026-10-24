#include "../../include/signatures/DigitalSignature.h"

namespace docflow {

namespace {
const std::size_t kMinHashLength = 6;
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

}
