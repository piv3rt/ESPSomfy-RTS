#ifndef statusled_h
#define statusled_h

#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

void initStatusLed();
void fadeToBlack(uint32_t);
void blinkStatusLed(uint32_t);
void clearStatusLed();
void resetStatusLed();
void fadeLoop();
void blinkLoop();
void ledLoop();
void setStatusLed(uint8_t r, uint8_t g, uint8_t b);

#endif
