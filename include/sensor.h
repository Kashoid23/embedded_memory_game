#pragma once

#include <Arduino.h>

namespace Sensor {
    constexpr uint16_t kDarkThreshold = 300;

    void setup();
    bool isDark();
}
