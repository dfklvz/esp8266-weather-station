#pragma once

#include <Arduino.h>

namespace Temperature {
    void init();
    float read(uint8_t index);  // index с 0, для вывода добавим 1
    uint8_t getCount();
}