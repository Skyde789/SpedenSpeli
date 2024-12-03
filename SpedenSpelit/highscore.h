#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <arduino.h>

extern byte currentScore;
extern byte topScores[4];

// Receives a score, and checks if it is in the top 4 and places it accordingly
bool CheckIfTopScore(byte);

// Writes a score to ROM addresses 0-3 are "top 1-4"
// Receives a score and an address
void WriteToROM(byte, byte);

// Read a value from an address and return it
byte ReadFromROM(byte);

// Returns a score from topScores[] with the correct index given
byte GetScore(int);

// Update the array of the top scores
void UpdateScores();

// Save ALL of the scores to ROM
void SaveScores();
#endif