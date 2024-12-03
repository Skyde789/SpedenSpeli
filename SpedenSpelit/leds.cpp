#include "leds.h"

int lastLedIndex = -1;

void initializeLeds() {
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void setLed(byte index) {
  index--;
  if (index >= 0 && index < ledCount) {
    if (lastLedIndex != -1) {
      digitalWrite(ledPins[lastLedIndex], LOW);
    }
    digitalWrite(ledPins[index], HIGH);
    lastLedIndex = index;
  }
}

void clearAllLeds() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  lastLedIndex = -1;
}

void setAllLeds() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  lastLedIndex = -1;
}

void show1() {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < ledCount; j++) {
      if (i & (1 << j)) {
        digitalWrite(ledPins[j], HIGH);
      } else {
        digitalWrite(ledPins[j], LOW);
      }
    }
    delay(200);
  }
  clearAllLeds();
}

void show2() {
  int delayTime = 100;
  for (int cycle = 0; cycle < 10; cycle++) {
    for (int i = 0; i < ledCount; i++) {

      digitalWrite(ledPins[i], HIGH);
      tone(7, (350 + i * 100), (1000 / 8));
      delay(delayTime);
      clearAllLeds();
    }
    delayTime = max(50, delayTime - 20);
  }
  clearAllLeds();
}
