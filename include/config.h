#pragma once
#include <Arduino.h>

// Часовой пояс UTC+5 (Караганда)
static const int32_t TIMEZONE_OFFSET = 5 * 3600;

// Интервалы обновления (миллисекунды)
static const uint32_t TEMP_INTERVAL_MS  = 2000;
static const uint32_t CLOCK_INTERVAL_MS = 1000;

// Датчик температуры
static const uint8_t TEMP_PIN        = D4;
static const uint8_t TEMP_RESOLUTION = 12;

// SD карта
static const uint8_t SD_CS_PIN = D3;

// LCD дисплей
static const uint8_t LCD_ADDRESS = 0x27;
static const uint8_t LCD_COLS    = 16;
static const uint8_t LCD_ROWS    = 2;

// WiFi
static const uint32_t WIFI_TIMEOUT_MS = 10000;
static const uint32_t NTP_TIMEOUT_MS  = 10000;

// Device
constexpr const char* DEVICE_HOSTNAME = "weather-station";
static const uint32_t SERIAL_BAUD_RATE = 115200;

// NTP синхронизация
static const bool NTP_SYNC_ON_START = false;

// Debug
static const bool DEBUG_ENABLED = false;

// Задержка после вывода результата на дисплей чтобы успеть прочитать результат (мс)
static const uint32_t DISPLAY_RESULT_DELAY_MS = 3000;

// Интервал между показаниями датчиков  температуры(мс)
static const uint32_t TEMP_DISPLAY_INTERVAL_MS = 3000;

// Значение температуры при ошибке датчика
static const float TEMP_ERROR_VALUE = -999.0f;
