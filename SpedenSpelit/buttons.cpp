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
  if (pin == 2)
  return 1;

  if (pin == 3)
  return 2;

  if (pin == 4)
  return 3;

  if (pin == 5)
  return 4;

  if (pin == 6)
  return 5;

  return -1;
}

ISR(PCINT2_vect) {

  if(canPress == false && gameRunning)
    return;
    
  if (gameRunning){
    for(int i = 2;i<6;i++)
    {
      byte luettu = digitalRead(i);
      //Serial.print("Button: ");
      //Serial.print(convert(i));
      //Serial.println(luettu==HIGH ? " True " : " False ");
      if(luettu==HIGH)
      {
        buttonPressed = convert(i);
            
        if(gameRunning)
          canPress = false;
      }
    }  
  }
  else
    if (digitalRead(6) == LOW)
      buttonPressed = 5;
}
