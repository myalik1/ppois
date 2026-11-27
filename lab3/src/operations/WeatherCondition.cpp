#include "../../include/operations/WeatherCondition.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kMaxSafeWindKnots = 40.0;
const double kMinSafeVisibilityMeters = 550.0;
const double kFreezingPointCelsius = 2.0;
}

WeatherCondition::WeatherCondition(double windSpeedKnots,
                                   double visibilityMeters,
                                   double temperatureCelsius,
                                   bool hasThunderstorm,
                                   bool isIcingCondition)
    : windSpeedKnots_(windSpeedKnots),
      visibilityMeters_(visibilityMeters),
      temperatureCelsius_(temperatureCelsius),
      hasThunderstorm_(hasThunderstorm),
      isIcingCondition_(isIcingCondition) {}

void WeatherCondition::verifySafeForFlight() const {
    if (hasThunderstorm_ || windSpeedKnots_ > kMaxSafeWindKnots ||
        visibilityMeters_ < kMinSafeVisibilityMeters) {
        throw WeatherHazardException("Severe weather prevents flight operations");
    }
}

bool WeatherCondition::requiresAircraftDeicing() const {
    return isIcingCondition_ || temperatureCelsius_ <= kFreezingPointCelsius;
}

void WeatherCondition::updateWeatherMetrics(double windKnots, double visibilityM, bool storm) {
    windSpeedKnots_ = windKnots;
    visibilityMeters_ = visibilityM;
    hasThunderstorm_ = storm;
}

double WeatherCondition::getWindSpeedKnots() const { return windSpeedKnots_; }
double WeatherCondition::getVisibilityMeters() const { return visibilityMeters_; }
double WeatherCondition::getTemperatureCelsius() const { return temperatureCelsius_; }
bool WeatherCondition::getHasThunderstorm() const { return hasThunderstorm_; }
bool WeatherCondition::getIsIcingCondition() const { return isIcingCondition_; }

}
