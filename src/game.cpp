#include <Arduino.h>
#include <vector>

#include "config.h"
#include "sensor.h"
#include "game.h"

namespace Game {
    namespace {
        std::vector<uint8_t> levelValues;

        uint8_t readButtonPress(uint8_t buttonPin, uint8_t ledPin) {
            if (digitalRead(buttonPin) != LOW) return 0;
            
            delay(kButtonDebounceTime);
            
            if (digitalRead(buttonPin) != LOW) return 0;

            unsigned long startTime = millis();
            while (digitalRead(buttonPin) == LOW) {
                delay(kButtonPollDelay);
                if (millis() - startTime > kButtonLongPressTime) {
                    break;
                }
            }

            return ledPin;
        }

        uint16_t setValues() {
            return (random(2) == 0) ? Config::kRightLedPin : Config::kLeftLedPin;
        }

        void stop() {
            unsigned long start = millis();

            while (millis() - start < kIlluminationLength) {
                digitalWrite(Config::kRightLedPin, HIGH);
                digitalWrite(Config::kLeftLedPin, HIGH);
                delay(kIlluminationBlinkDelay);

                digitalWrite(Config::kRightLedPin, LOW);
                digitalWrite(Config::kLeftLedPin, LOW);
                delay(kIlluminationBlinkDelay);
            }

            levelValues.clear();
        }

        void generateLevelValues() {
            if (levelValues.size() >= kMaxLevel) {
                stop();
            }

            levelValues.push_back(setValues());
        }

        void displayLevelValues() {
            for (uint16_t pin : levelValues) {
                digitalWrite(pin, HIGH);
                delay(kLevelDisplayDelay);
                digitalWrite(pin, LOW);
                delay(kLevelDisplayDelay);
            }
        }

        uint8_t getButtonValues() {
            const ButtonConfig buttons[] = {
                { Config::kRightButtonPin, Config::kRightLedPin },
                { Config::kLeftButtonPin,  Config::kLeftLedPin  }
            };

            while (true) {
                for (const auto& btn : buttons) {
                    if (uint8_t press = readButtonPress(btn.pin, btn.ledPin)) {
                        return press;
                    }
                }
                delay(5);
            }
        }

        bool correctAnswer() {
            for (const uint8_t expectedPin : levelValues) {
                if (getButtonValues() != expectedPin) {
                    stop();
                    return false;
                }
            }

            return true;
        }
    }

    void setup() {
        Serial.begin(Config::kBaud);

        pinMode(Config::kRightLedPin, OUTPUT);
        pinMode(Config::kLeftLedPin, OUTPUT);

        pinMode(Config::kRightButtonPin, INPUT_PULLUP);
        pinMode(Config::kLeftButtonPin, INPUT_PULLUP);

        Sensor::setup();
        randomSeed(analogRead(A0));

        levelValues.reserve(kMaxLevel);
    }

    void start() {
        if (Sensor::isDark()) {
            return;
        }

        generateLevelValues();
        displayLevelValues();

        if (correctAnswer()) {
            delay(kLevelDelay);
        }
    }
}
