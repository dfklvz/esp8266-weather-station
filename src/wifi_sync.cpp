#include "wifi_sync.h"
#include "credentials.h"
#include "config.h"
#include "clock.h"
#include "display.h"
#include "logger.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

static WiFiUDP ntpUDP;
static NTPClient timeClient(ntpUDP, "pool.ntp.org", TIMEZONE_OFFSET);

static const char* SPINNER[] = {"|", "/", "-", "\\"};
static uint8_t spinnerIndex = 0;

namespace WifiSync {

    bool syncTime() {
        Logger::info("Connecting to WiFi...");
        WiFi.hostname(DEVICE_HOSTNAME);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        uint32_t startTime = millis();
        while (WiFi.status() != WL_CONNECTED) {
            if (millis() - startTime >= NTP_TIMEOUT_MS) {
                Logger::info("WiFi connection timeout!");
                WiFi.disconnect();
                return false;
            }
            delay(500);
            Logger::progress(".");
            Display::updateLine1("Syncing time " + String(SPINNER[spinnerIndex % 4]));
            spinnerIndex++;
        }

        Logger::info("\nWiFi connected: " + WiFi.localIP().toString());
        Logger::info("Hostname:       " + String(WiFi.hostname()));
        Logger::info("MAC:            " + WiFi.macAddress());

        timeClient.begin();
        if (!timeClient.update()) {
            Logger::info("NTP sync failed!");
            WiFi.disconnect();
            return false;
        }

        // Передаём время в DS3231
        time_t epochTime = timeClient.getEpochTime();
        struct tm* ptm = gmtime(&epochTime);

        Clock::setTime(
            ptm->tm_year + 1900,  // tm_year считается от 1900
            ptm->tm_mon + 1,      // tm_mon от 0 до 11
            ptm->tm_mday,
            ptm->tm_hour,
            ptm->tm_min,
            ptm->tm_sec
        );

        Logger::info("Time synced: " + Clock::getTime() +
            " (UTC+" + String(TIMEZONE_OFFSET / 3600) + ")");

        timeClient.end();
        WiFi.disconnect();
        Logger::info("WiFi disconnected");

        return true;
    }

}