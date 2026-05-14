#include "storage.h"
#include "config.h"
#include "logger.h"
#include <SD.h>
#include <SPI.h>

static bool sdAvailable = false;

namespace Storage {

    void init() {
        if (!SD.begin(SD_CS_PIN)) {
            Logger::info("SD card not found!");
            return;
        }

        sdAvailable = true;
        Logger::info("SD card found!");
        Logger::info("SD size: " + String(SD.size() / 1024 / 1024) + " MB");
    }

    bool isAvailable() {
        return sdAvailable;
    }

}