#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "highscore.h"
#include "SpedenSpelit.h"
#include "sounds.h"
// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile byte buttonPressed = -1;          // for buttons interrupt handler
volatile bool gameTimerReady = false;      // for timer interrupt handler
bool gameRunning = false;
int timerReduction = 624;                  // timer is 0-62499 1 second, so reduce the timer by 0.01s per point

unsigned long millisTimer = 0;             // millis() handling
int showScoreDelay = 0;                    // how long do we show the highscores
int loseGameDelay = 1500;
byte buttonInputDelay = 75;                // Every X ms check if the latest button was correct? 
byte highScoreIndex = 0;                   // highscore index

byte targetLeds[100];
byte playerIndex = 0;
byte gameIndex = 0;

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
    if (millis() - millisTimer >= buttonInputDelay)
      if(buttonPressed>=1 && buttonPressed <= 4)
        checkGame(buttonPressed);

    if(gameTimerReady) 
        PrepareNew();
    
    if (millis() - millisTimer >= loseGameDelay)
      LoseGame();
  }
  // Idle behaviour like showing highscores and such
  else
  {
    if (buttonPressed == 5)
      startTheGame();
    if (millis() - millisTimer >= showScoreDelay)
      ShowHighScore();
  }
}

void ShowHighScore()
{
  if (gameRunning)
    return;

  showScoreDelay = 5000;
  showResult(GetScore(highScoreIndex));
  setLed(highScoreIndex+1);
  highScoreIndex++;
  if (highScoreIndex > 3)
    highScoreIndex = 0;
  millisTimer = millis();
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

  OCR1A = max(12500, (62499 - gameIndex * timerReduction));
}

void LoseGame(){
  gameRunning = false;
  buttonPressed = -1;
  highScoreIndex = 0;
  Serial.println("Game lost!");
  clearAllLeds();
  initializeTimer(false);
 
  GameOverSound();
  
  if (CheckIfTopScore(currentScore))
    show2();

}

void PrepareNew()
{
  clearAllLeds();
  Serial.println(targetLeds[gameIndex]);
  setLed(targetLeds[gameIndex]);
  LedPopSound(gameIndex);
  
  gameIndex++;
  gameTimerReady = false;
}

void checkGame(byte buttonNum)
{ 
  Serial.print("Check Game: ");
  
  if (buttonNum == targetLeds[playerIndex])
  {
    Serial.println("Correct!");
    currentScore++;
    showResult(currentScore);
  }
  else{
    Serial.println("Wrong!");
    LoseGame();
  }

  millisTimer = millis();
  buttonPressed = -1;
}

void initializeGame()
{
  gameTimerReady = false;
  currentScore = 0;
  gameIndex = 0;
  playerIndex = 0;
  buttonPressed = -1;

  millisTimer = millis();
  randomSeed(millis());
 
  for(int i = 0; i < 100; i++)
  {
    targetLeds[i] = random(1,5);
  }

  initializeTimer(true);
  PrepareNew();
}

void startTheGame()
{
  clearAllLeds();
  showResult(0);
  GameStartSound();
  gameRunning = true;

  delay(1000);

  Serial.println("Game started!");
  initializeGame();
}