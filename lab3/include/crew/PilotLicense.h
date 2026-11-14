#pragma once
#include <string>

namespace airport {

class PilotLicense {
private:
    std::string licenseNumber_;
    std::string aircraftTypeRating_;
    int issueYear_;
    int expiryYear_;
    bool hasInstrumentRating_;

public:
    PilotLicense(const std::string& licenseNumber,
                 const std::string& aircraftTypeRating,
                 int issueYear,
                 int expiryYear,
                 bool hasInstrumentRating);

    bool isLicenseValid(int currentYear) const;
    bool matchesAircraftModel(const std::string& modelName) const;
    void renewLicense(int additionalYears);

    const std::string& getLicenseNumber() const;
    const std::string& getAircraftTypeRating() const;
    int getIssueYear() const;
    int getExpiryYear() const;
    bool getHasInstrumentRating() const;
};

}
