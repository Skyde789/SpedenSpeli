#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>

const byte ledPins[] = {A0, A1, A2, A3};
const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

// Funktiot
void initializeLeds();
void setLed(byte index);
void clearAllLeds();
void setAllLeds();
void show1();
void show2();

#endif
