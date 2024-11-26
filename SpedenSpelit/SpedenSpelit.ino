#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "highscore.h"
#include "SpedenSpelit.h"
#include "sounds.h"
// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile byte buttonPressed = -1;           // for buttons interrupt handler
volatile bool gameTimerReady = false;  // for timer interrupt handler
bool gameRunning = false;
int timerScoreReduction = 624; // timer is 0-62499 1 second, so reduce the timer by 0.01s per point
bool doFail = false;

byte randomizedTarget = -1;
byte currentScore = 0;

void setup()
{
  Serial.begin(9600);

  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();

  UpdateScores();
  Serial.println("Setup Done!");
}

void loop()
{
  if(gameRunning)
  {
    if(buttonPressed>=1 && buttonPressed <= 4)
      checkGame(buttonPressed);

    if(gameTimerReady) 
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

void initializeTimer(bool on)
{
	 // Ajastimen asetukset
  cli();                                // Keskeytykset pois päältä asetuksen ajaksi
  if(on)
  {                    
    TCCR1A = 0;                           // Nollataan TCCR1A-rekisteri
    TCCR1B = 0;                           // Nollataan TCCR1B-rekisteri
  
    TCCR1B |= (1 << WGM12);               // Asetetaan CTC-tila (WGM12 = 1) (Clear timer on compare match)

    TIMSK1 |= (1 << OCIE1A);              // Keskeytys, kun OCR1A arvo saavutetaan

    TCCR1B |= B00000100;                  // Asetetaan prescaler 256           

    OCR1A = 62499;   
  }
  else
  {
    TCCR1A = 0;                        
    TCCR1B = 0; 

    TIMSK1 = 0;

    OCR1A = 0;
  }

  sei();                                // Keskeytykset takaisin päälle
}

ISR(TIMER1_COMPA_vect)
{
  gameTimerReady = true;
}

void LoseGame(){
  gameRunning = false;
  buttonPressed = -1;

  clearAllLeds();
  showResult(0);
  initializeTimer(false);

  GameOverSound();
  Serial.println("Game lost!");
  
  CheckIfTopScore(currentScore);
}

void PrepareNew(){
  randomizedTarget = random(1,5);
  Serial.println(randomizedTarget);
  setLed(randomizedTarget);

  gameTimerReady = false;
  doFail = true;
  
  buttonPressed = -1;
  canPress = true;
  
}

void checkGame(byte buttonNum)
{ 
  Serial.print("Check Game: ");
  clearAllLeds();
  if (buttonNum == randomizedTarget)
  {
    Serial.println("Correct!");
    currentScore++;
    showResult(currentScore);

    doFail = false;
    OCR1A = max(12500, (62499 - currentScore * timerScoreReduction));
  }
  else{
    Serial.println("Wrong!");
    LoseGame();
  }

  buttonPressed = -1;
  canPress = false;
}

void initializeGame()
{
  canPress = false;
  gameRunning = true;
  gameTimerReady = false;
  currentScore = 0;
  buttonPressed = -1;

  clearAllLeds();
  randomSeed(millis());
  initializeTimer(true);
  PrepareNew();
}

void startTheGame()
{
  GameStartSound();
  Serial.println("Game started!");
  initializeGame();
}

