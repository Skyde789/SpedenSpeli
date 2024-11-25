#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <arduino.h>

extern byte currentScore;
extern byte topScores[4];

// Receives a score, and checks if it is in the top 4 and places it accordingly
void CheckTopScore(byte);

// Writes a score to ROM addresses 0-3 are "top 1-4"
// Receives a score and an address
void WriteToROM(byte, byte);

// Read a value from an address and return it
byte ReadFromROM(byte);

// Update the array of the top scores
void GetTopScores();

#endif