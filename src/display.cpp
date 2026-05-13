#include "display.h"
#include "config.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

static LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

static String padLine(const String& text) {
    String padded = text;
    while (padded.length() < LCD_COLS) {
        padded += ' ';
    }
    return padded;
}

namespace Display {

    void init() {
        lcd.init();
        lcd.backlight();
        lcd.clear();
    }

    void showText(const String& line1, const String& line2) {
        updateLine1(line1);
        updateLine2(line2);
    }

    void updateLine1(const String& text) {
        lcd.setCursor(0, 0);
        lcd.print(padLine(text));
    }

    void updateLine2(const String& text) {
        lcd.setCursor(0, 1);
        lcd.print(padLine(text));
    }

    void clear() {
        lcd.clear();
    }

}