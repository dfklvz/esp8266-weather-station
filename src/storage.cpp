#include "storage.h"
#include "config.h"
#include "logger.h"
#include <SD.h>
#include <SPI.h>

static bool sdAvailable = false;
static uint64_t sdSize = 0;

namespace Storage {

    void init() {
        if (!SD.begin(SD_CS_PIN)) {
            Logger::info("SD card not found!");
            return;
        }

        sdAvailable = true;
        sdSize = SD.size() / 1024 / 1024;
        Logger::info("SD card found! Size: " + String((uint32_t)sdSize) + " MB");
    }

    bool isAvailable() {
        return sdAvailable;
    }

    uint64_t getSize() {
        return sdSize;
    }

}