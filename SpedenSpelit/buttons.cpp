#include "buttons.h"
bool canPress = true;


void initButtonsAndButtonInterrupts(void)
{
    
    pinMode(2,INPUT_PULLUP);
    pinMode(3,INPUT_PULLUP);
    pinMode(4,INPUT_PULLUP);
    pinMode(5,INPUT_PULLUP);
    pinMode(6,INPUT_PULLUP);
    
    PCICR |= B00000100;
    PCMSK2 = B01111100;
}

int convert (int pin)
{
  return (pin-1) > 0 ? (pin-1) : -1;
}

ISR(PCINT2_vect) {
  for(int i = 2;i<7;i++)
  {
    byte luettu = digitalRead(i);
    if(luettu==LOW)
    {
      buttonPressed = convert(i);
            
      if(gameRunning)
        canPress = false;
    }
  }  
}
