#pragma once

#include "../documents/Document.h"
#include <string>

namespace docflow {

class DigitalSignature {
public:
    DigitalSignature(
        std::string sigId, std::string docId, std::string certSerial, std::string sigHash);
    bool matchesDocument(const Document& document) const;
    bool validateHashFormat() const;
    const std::string& getSignatureHash() const;

private:
    std::string signatureId_;
    std::string documentId_;
    std::string signerCertSerial_;
    std::string signatureHash_;
};

}
