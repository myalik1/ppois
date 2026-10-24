#pragma once

#include <string>

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

}
