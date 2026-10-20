#include <Arduino.h>

#include "config.h"
#include "sensor.h"

namespace Sensor {
    void setup() {
        pinMode(Config::kLdrPin, INPUT);
    }

    int readLdr() {
        return analogRead(Config::kLdrPin);
    }

    bool isDark() {
        return readLdr() < kDarkThreshold;
    }
}
