#ifndef SOUNDS_H
#define SOUNDS_H
#include <arduino.h>

const int soundPin = 7;
void GameOverSound();
void LedPopSound(byte);

void GameStartSound();

void PlaySound(int*, int*, int);

#endif