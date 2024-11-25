#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile byte buttonPressed = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
bool gameRunning = false;
int timerScoreReduction = 624; // timer is 0-62499 1 second, so reduce the timer by 0.01s per point
bool doFail = false;

byte randomizedTarget = -1;

byte currentScore = 0;
byte topScores[4];

void setup()
{
  Serial.begin(9600);
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();
}

void loop()
{
  if(gameRunning)
  {
    if(buttonPressed>=1 && buttonPressed <= 4)
      checkGame(buttonPressed);

    if(newTimerInterrupt) 
    {
      if (doFail)
        LoseGame();
      else
        PrepareNew();
      
      
    }
  }
  // Idle behaviour like showing highscores and such
  else
  {
    if (buttonPressed == 5)
      startTheGame();
  }
}

void initializeTimer(void)
{
	 // Ajastimen asetukset
  cli();                                // Keskeytykset pois päältä asetuksen ajaksi
  TCCR1A = 0;                           // Nollataan TCCR1A-rekisteri
  TCCR1B = 0;                           // Nollataan TCCR1B-rekisteri
  
  TCCR1B |= (1 << WGM12);               // Asetetaan CTC-tila (WGM12 = 1) (Clear timer on compare match)
                                        // B00001000 WGM12

  TIMSK1 |= (1 << OCIE1A);              // Keskeytys, kun OCR1A arvo saavutetaan
                                        // B00000010 OCR1A

  TCCR1B |= B00000100;                  // Asetetaan prescaler 256           
                                        // Eri prescalereitä                  Kuin monta kertaa timer päivittyy sekunnissa
                                        // B00000001 1    = 16 000 000 / 1    = 16 000 000 kertaa sekunnissa
                                        // B00000010 8    = 16 000 000 / 8    = 2 000 000 kertaa sekunnissa
                                        // B00000011 64   = 16 000 000 / 64   = 250 000 kertaa sekunnissa
                                        // B00000100 256  = 16 000 000 / 256  = 62 500 kertaa sekunnissa
                                        // B00000101 1024 = 16 000 000 / 1024 = 15 264 kertaa sekunnissa

  OCR1A = 62499;   

  sei();                                // Keskeytykset takaisin päälle
}

ISR(TIMER1_COMPA_vect)
{
  // If the game is not running, leave
  if(!gameRunning)
    return;

  newTimerInterrupt = true;
}

void LoseGame(){
  gameRunning = false;
  showResult(0);
  // TODO Check if the current score if in the top 4 scores
}
void PrepareNew(){
  randomizedTarget = random(1,5);
  setLed(randomizedTarget);
  newTimerInterrupt = false;
  canPress = true;
  doFail = true;
}
void checkGame(byte buttonNum)
{
  if (buttonNum == randomizedTarget)
  {
    currentScore++;
    clearAllLeds();
    showResult(currentScore);
    doFail = false;
    OCR1A = max(12500, (62499 - currentScore * timerScoreReduction));
  }
  else
    LoseGame();

  buttonPressed = -1;
  canPress = false;
}


void initializeGame()
{
  gameRunning = true;
  clearAllLeds();
  randomSeed(millis());

  initializeTimer();

  currentScore = 0;
  buttonPressed = -1;
}

void startTheGame()
{
   initializeGame();

}

