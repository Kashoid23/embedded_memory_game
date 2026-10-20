#pragma once

#include <Arduino.h>

namespace Game {
    constexpr uint8_t kMaxLevel = 5;
    constexpr uint16_t kIlluminationTime = 3000;
    constexpr uint16_t kButtonDebounceTime = 30;
    constexpr uint16_t kButtonPollDelay = 1;
    constexpr uint16_t kButtonLongPressTime = 2000;
    constexpr uint16_t kLevelDelay = 1000;
    constexpr uint16_t kLevelDisplayDelay = 500;
    constexpr uint16_t kIlluminationLength = 3000;
    constexpr uint16_t kIlluminationBlinkDelay = 250;

    struct ButtonConfig {
        uint8_t pin;
        uint8_t ledPin;
    };

    void setup();
    void start();
}
