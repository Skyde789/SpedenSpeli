#ifndef DISPLAY_H
#define DISPLAY_H
#include <arduino.h>

const int dataPin1 = 8;    
const int clockPin1 = 9;   
const int latchPin1 = 10;  
const int dataPin2 = 11;    
const int clockPin2 = 12;   
const int latchPin2 = 13;   

// Valmis taulukko binääriluvuista, joka auttaa piiriä näyttämään oikean luvun (esim. "digitPatterns[3]" näyttäisi 3)
const byte digitPatterns[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

/*
  Laittaa tarvittavat pinnit OUTPUT tilaan
*/
void initializeDisplay(void);

/*
Näyttää kahdessa displayssä kympit ja ykköset
Saa parametrinä kympit ja ykköset erikseen
*/
void writeHighAndLowNumber(uint8_t tens,uint8_t ones);

/*
  Eroittaa kympit ja ykköset luvusta ja kutsuu writeHighAndLowNumber funktion eroitetuilla luvuilla
*/
void showResult(byte result);

#endif
