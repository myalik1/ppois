#pragma once

#include "../core/IdentityAndAccess.h"
#include "../documents/DocumentCore.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>

namespace docflow {

class CryptoHasher {
public:
    CryptoHasher(std::string algorithm, std::string saltPrefix, int iterations);
    std::string computeDigest(const std::string& payload) const;
    bool verifyDigest(const std::string& payload, const std::string& expectedDigest) const;

private:
    std::string algorithmName_;
    std::string saltPrefix_;
    int iterationCount_;
};

class Certificate {
public:
    Certificate(
        std::string serial, std::string holderUserId, std::string issuer, int validUntil, bool revoked);
    void revokeCertificate();
    bool isValidForUser(const User& user, int currentDay) const;
    const std::string& getSerialNumber() const;

private:
    std::string serialNumber_;
    std::string holderUserId_;
    std::string issuerName_;
    int validUntilDay_;
    bool revokedFlag_;
};

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

class OfficialStamp {
public:
    OfficialStamp(std::string code, std::string orgName, std::string regNumber);
    std::string formatStampMark() const;
    bool belongsToOrganization(const std::string& orgName) const;

private:
    std::string stampCode_;
    std::string organizationName_;
    std::string registrationNumber_;
};

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
