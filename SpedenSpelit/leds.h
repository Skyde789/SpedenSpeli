#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <Arduino.h>

const byte ledPins[] = {A2, A3, A4, A5};
const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

// Funktiot
void setupLeds();
void setLed(byte index);
void clearAllLeds();
void setAllLeds();
void show1();
void show2();

#endif
