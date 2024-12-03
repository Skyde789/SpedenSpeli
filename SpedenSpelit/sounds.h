#ifndef SOUNDS_H
#define SOUNDS_H
#include <arduino.h>

const int soundPin = 7;
// Plays a jingle when you lose
void GameOverSound();

// Plays a beep when a new led appears, increasing in frequency with currentScore.
void LedPopSound(byte);

// Plays a jingle when you start
void GameStartSound();

// Receives 2 pointers, an array of frequencies and an array of durations. Also receives the array length
// Play each of the sounds with delays inbetween
void PlaySound(int*, int*, int);

#endif