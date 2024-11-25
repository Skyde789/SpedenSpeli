#include "display.h"


void initializeDisplay(void)
{
  pinMode(dataPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(latchPin1, OUTPUT);

  pinMode(dataPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(latchPin2, OUTPUT);
}

void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
  digitalWrite(latchPin1, LOW);              // Prepare to shift data
  shiftOut(dataPin1, clockPin1, MSBFIRST, digitPatterns[ones]);  // Send pattern
  digitalWrite(latchPin1, HIGH);             // Latch the data to display

  digitalWrite(latchPin2, LOW);              // Prepare to shift data
  shiftOut(dataPin2, clockPin2, MSBFIRST, digitPatterns[tens]);  // Send pattern
  digitalWrite(latchPin2, HIGH);             // Latch the data to display
}

void showResult(byte number)
{
int tens = 0;
int ones = 0;

while(number >= 10){
  tens++; // tens = tens + 1; TAI tens += 1;
  number -= 10; // number = number - 10;
}

  ones = number;

  writeHighAndLowNumber(tens, ones);
}

