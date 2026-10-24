#pragma once

#include "../core/User.h"
#include "../documents/Document.h"
#include "Certificate.h"
#include "CryptoHasher.h"
#include "DigitalSignature.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>

namespace docflow {

class SignatureService {
public:
    SignatureService(std::string serviceName, CryptoHasher hasher);
    DigitalSignature signDocument(
        const Document& document, const User& signer, const Certificate& cert, int currentDay);
    bool verifyDocumentSignatures(
        const Document& document, const Certificate& cert, int currentDay) const;
    std::size_t countSignatures(const std::string& documentId) const;

private:
    std::string serviceName_;
    CryptoHasher hasher_;
    std::map<std::string, std::vector<DigitalSignature>> signaturesByDoc_;
};

}
