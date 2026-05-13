#include "temperature.h"
#include "config.h"
#include "logger.h"
#include <OneWire.h>
#include <DallasTemperature.h>

static OneWire oneWire(TEMP_PIN);
static DallasTemperature sensor(&oneWire);
static uint8_t sensorCount = 0;

namespace Temperature {

    void init() {
        sensor.begin();
        sensor.setResolution(TEMP_RESOLUTION);

        sensorCount = sensor.getDeviceCount();

        if (sensorCount == 0) {
            Logger::info("Temperature sensors not found!");
            return;
        }

        Logger::info("Temperature sensors found: " + String(sensorCount));

        DeviceAddress address;
        for (uint8_t i = 0; i < sensorCount; i++) {
            if (sensor.getAddress(address, i)) {
                String addr = "Sensor " + String(i + 1) + " address: ";
                for (uint8_t j = 0; j < 8; j++) {
                    if (address[j] < 16) addr += "0";
                    addr += String(address[j], HEX);
                    if (j < 7) addr += ":";
                }
                Logger::info(addr);
            }
        }
    }

    float read(uint8_t index) {
        sensor.requestTemperatures();
        float temp = sensor.getTempCByIndex(index);

        if (temp == -127.0f) {
            Logger::info("Sensor " + String(index + 1) + " error!");
            return TEMP_ERROR_VALUE;
        }

        return temp;
    }

    uint8_t getCount() {
        return sensorCount;
    }

}