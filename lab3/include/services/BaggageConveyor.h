#pragma once
#include <string>
#include "../passengers/BaggageItem.h"

namespace airport {

class BaggageConveyor {
private:
    std::string beltId_;
    double maxLoadKg_;
    double currentLoadKg_;
    int bagsOnBelt_;
    bool isRunning_;

public:
    BaggageConveyor(const std::string& beltId,
                    double maxLoadKg,
                    bool isRunning = false);

    void startBelt();
    void stopBelt();
    void loadBaggageOntoBelt(const BaggageItem& item);
    void unloadAllBaggage();

    const std::string& getBeltId() const;
    double getMaxLoadKg() const;
    double getCurrentLoadKg() const;
    int getBagsOnBelt() const;
    bool getIsRunning() const;
};

}
