#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "temperature.h"
#include "clock.h"
#include "logger.h"
#include "wifi_sync.h"
#include "storage.h"

static uint32_t lastTempTime  = 0;
static uint32_t lastClockTime = 0;
static uint8_t  currentSensor = 0;

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    delay(500);

    Display::init();
    Temperature::init();
    Clock::init();
    Storage::init(); 

    if (Storage::isAvailable()) {
        Display::showText("SD card found!", String((uint32_t)Storage::getSize()) + " MB");
    } else {
        Display::showText("SD card", "not found!");
    }

    delay(DISPLAY_RESULT_DELAY_MS);

    if (NTP_SYNC_ON_START) {
        Logger::info("NTP sync starting...");
        Display::showText("Syncing time...", "Please wait");

        if (WifiSync::syncTime()) {
            Display::showText("Time synced!", Clock::getTime());
            Logger::info("NTP sync success: " + Clock::getTime());
        } else {
            Display::showText("Sync failed!", "Using RTC time");
            Logger::info("NTP sync failed, using RTC time");
        }
    } else {
        Display::showText("NTP sync", "disabled");
        Logger::info("NTP sync disabled, using RTC time");
    }

    delay(DISPLAY_RESULT_DELAY_MS);

    Logger::info("=== ESP8266 OK ===");
}

void loop() {
    uint32_t now = millis();

    if (now - lastClockTime >= CLOCK_INTERVAL_MS) {
        lastClockTime = now;
        Display::updateLine1(Clock::getTime());
    }

    if (now - lastTempTime >= TEMP_DISPLAY_INTERVAL_MS) {
        lastTempTime = now;

        float temp = Temperature::read(currentSensor);
        String label = "Temp " + String(currentSensor + 1) + "/" + String(Temperature::getCount()) + ": ";
        String tempStr = (temp == TEMP_ERROR_VALUE)
            ? label + "--.- C"
            : label + String(temp, 1) + " C";

        Logger::debug(Clock::getTime() + " | " + tempStr);
        Display::updateLine2(tempStr);

        // Переключаемся на следующий датчик
        currentSensor = (currentSensor + 1) % Temperature::getCount();
    }
}