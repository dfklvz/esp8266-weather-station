#include "clock.h"
#include "logger.h"
#include <RTClib.h>

static RTC_DS3231 rtc;

namespace Clock {

    void init() {
        if (!rtc.begin()) {
            Logger::info("DS3231 not found!");
            return;
        }

        if (rtc.lostPower()) {
            Logger::info("RTC lost power, setting time...");
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }

        Logger::info("Clock initialized");
    }

    void setTime(uint16_t year, uint8_t month, uint8_t day,
                uint8_t hour, uint8_t minute, uint8_t second) {
        rtc.adjust(DateTime(year, month, day, hour, minute, second));
    }
    
    String getTime() {
        DateTime now = rtc.now();
        char buf[16];
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d",
                 now.hour(), now.minute(), now.second());
        return String(buf);
    }

    String getDate() {
        DateTime now = rtc.now();
        char buf[16];
        snprintf(buf, sizeof(buf), "%02d.%02d.%04d",
                 now.day(), now.month(), now.year());
        return String(buf);
    }

    bool isRunning() {
        return !rtc.lostPower();
    }

}