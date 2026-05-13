#pragma once

#include <Arduino.h>
#include "config.h"

namespace Logger {

    // Всегда пишем — важные системные события
    inline void info(const String& message) {
        Serial.println(message);
    }

    // Только если debug включен — подробности работы
    inline void debug(const String& message) {
        if (DEBUG_ENABLED) {
            Serial.println(message);
        }
    }

    // Для точек прогресса — без переноса строки
    // Всегда выводится, это важный индикатор подключения
    inline void progress(const String& message) {
        Serial.print(message);
    }

}