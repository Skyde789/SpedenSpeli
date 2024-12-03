#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>

const byte ledPins[] = {A0, A1, A2, A3};
const int ledCount = 4;

// Funktiot
// Asettaa kaikki led-pinnit OUTPUT tilaan
void initializeLeds();
// Asettaa ledin päälle ja samuttaa edellisen, joka on laitettu viimeksi päälle
void setLed(byte index);
// Laittaa kaikki ledit kiinni
void clearAllLeds();
// Laittaa kaikki ledit päälle
void setAllLeds();
// Näyttää binäärilaskun 0-15 neljän ledin avulla 
void show1();
// Tekee ledi aallon kiihdyttäen sekä se pitää samalla ääntä
void show2();

#endif
