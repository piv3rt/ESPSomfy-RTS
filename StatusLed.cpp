#include "ConfigSettings.h"
#include "StatusLed.h"

extern Adafruit_NeoPixel statusLed;
extern ConfigSettings settings;
unsigned long fadeStart;
uint32_t fadeMs;
uint32_t blinkMs;

struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color;

void initStatusLed() {
    if (settings.statusLedPin == 0) return;
    statusLed.setPin(settings.statusLedPin);
    statusLed.begin();
    resetStatusLed();
}

void saveCurrentColor() {
    uint32_t current = statusLed.getPixelColor(0);
    color.r = current >> 16 & 0xff;
    color.g = current >> 8 & 0xff;
    color.b = current & 0xff;
}

void fadeToBlack(uint32_t ms) {
    saveCurrentColor();
    fadeStart = millis();
    fadeMs = ms;
}

void blinkStatusLed(uint32_t ms) {
    saveCurrentColor();
    blinkMs = ms;
}

void clearStatusLed() {
    statusLed.clear();
    statusLed.show();
}

void resetStatusLed() {
    clearStatusLed();
    fadeMs = 0;
    blinkMs = 0;
}

void fadeLoop() {
    uint32_t elapsed = millis() - fadeStart;
    if (elapsed > fadeMs) {
        resetStatusLed();
        return;
    }
    uint8_t r = color.r - (color.r  * elapsed) / fadeMs;
    uint8_t g = color.g - (color.g  * elapsed) / fadeMs;
    uint8_t b = color.b - (color.b  * elapsed) / fadeMs;
    statusLed.setPixelColor(0, r, g, b);
    statusLed.show();
}

void blinkLoop() {
    if (millis() / blinkMs % 2 == 0) {
        statusLed.setPixelColor(0, color.r, color.g, color.b);
        statusLed.show();
        return;
    }
    clearStatusLed();
}

void ledLoop() {
    if (settings.statusLedPin == 0) return;
    if (fadeMs) fadeLoop();
    else if (blinkMs) blinkLoop();
}

void setStatusLed(uint8_t r, uint8_t g, uint8_t b) {
    if (settings.statusLedPin == 0) return;
    resetStatusLed();
    statusLed.setPixelColor(0, r, g, b);
    statusLed.show();
}
