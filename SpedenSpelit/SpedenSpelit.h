#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// receives a bool to either initialize the timer to be active or inactive
void initializeTimer(bool);

// Intoduce TIMER1_COMPA_vect Interrupt SeRvice (ISR) function for timer.
ISR(TIMER1_COMPA_vect);

// Initialize all variables to default values for a new game
void initializeGame(void);

// Check if the user pressed the correct button, handle losing if wrong.
void checkGame(byte);

// Does things before initializing the game.
void startTheGame(void);

// Prepares a new 1-4 led 
void PrepareNew()

// Stop the game, and check if the score is in the top 4. Play a jingle if true
void LoseGame()

//  Shows the top 4 scores in descending order
void ShowHighScore()
#endif