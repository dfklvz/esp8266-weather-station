#pragma once

#include <Arduino.h>

namespace Display {
    void init();
    void showText(const String& line1, const String& line2);
    void updateLine1(const String& text);
    void updateLine2(const String& text);
    void clear();
}