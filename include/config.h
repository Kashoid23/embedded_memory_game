#pragma once

#include <Arduino.h>

namespace Config {
    constexpr uint32_t kBaud = 115200;

    constexpr uint8_t kRightLedPin = 4;
    constexpr uint8_t kLeftLedPin = 5;
    constexpr uint8_t kRightButtonPin = 6;
    constexpr uint8_t kLeftButtonPin = 7;
    constexpr uint8_t kLdrPin = 8;
}
