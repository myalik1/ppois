#pragma once

namespace airport {

class WeatherCondition {
private:
    double windSpeedKnots_;
    double visibilityMeters_;
    double temperatureCelsius_;
    bool hasThunderstorm_;
    bool isIcingCondition_;

public:
    WeatherCondition(double windSpeedKnots,
                     double visibilityMeters,
                     double temperatureCelsius,
                     bool hasThunderstorm,
                     bool isIcingCondition);

    void verifySafeForFlight() const;
    bool requiresAircraftDeicing() const;
    void updateWeatherMetrics(double windKnots, double visibilityM, bool storm);

    double getWindSpeedKnots() const;
    double getVisibilityMeters() const;
    double getTemperatureCelsius() const;
    bool getHasThunderstorm() const;
    bool getIsIcingCondition() const;
};

}
