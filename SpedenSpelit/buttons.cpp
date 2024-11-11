#include "buttons.h"
int buttonPressed;
bool canPress = true;



void initButtonsAndButtonInterrupts(void)
{
    
    pinMode(2,INPUT_PULLUP);
    pinMode(3,INPUT_PULLUP);
    pinMode(4,INPUT_PULLUP);
    pinMode(5,INPUT_PULLUP);
    
    PCICR |= B00000100;
    PCMSK2 = B00111100;
}

ISR(PCINT2_vect) {

  if(canPress == false)
    return;
    
    for(int i = 2;i<6;i++)
    {
        byte luettu = digitalRead(i);
        
        /*while(digitalRead(i)==LOW)
    {
      //odotellaan, etta kayttaja nostaa napin
    }*/
        
        if(luettu==LOW)
        {
            buttonPressed = i;
            canPress = false;
        }
        
    }  
   /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */
}
