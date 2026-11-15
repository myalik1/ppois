#pragma once
namespace airport {

class LandingGear {
private:
    int strutCount_;
    double tirePressurePsi_;
    double brakeWearPercent_;
    bool isDeployed_;

public:
    LandingGear(int strutCount,
                double tirePressurePsi,
                double brakeWearPercent,
                bool isDeployed = true);

    void deployGear();
    void retractGear();
    void inspectLandingGear() const;

    int getStrutCount() const;
    double getTirePressurePsi() const;
    double getBrakeWearPercent() const;
    bool getIsDeployed() const;
};

}
