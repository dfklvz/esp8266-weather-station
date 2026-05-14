#pragma once

#include <Arduino.h>

namespace Storage {
    void init();
    bool isAvailable();
    uint64_t getSize();
}