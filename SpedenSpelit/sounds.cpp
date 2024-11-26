#include "sounds.h"

void GameOverSound()
{
  int sound[] = { 330, 294, 262, 196, 220, 196, 165, 131 }; 
  int duration[] = { 4, 4, 4, 4, 4, 8, 8, 2 };          

  PlaySound(sound, duration, 8);
}

void GameStartSound()
{
  int sound[] = { 262, 330, 392, 523, 392, 523, 659, 784 };
  int duration[] = { 8, 8, 8, 4, 8, 8, 8, 2 };              

  PlaySound(sound, duration, 8);
}

void PlaySound(int* sound, int* duration, int length){
  // iterate over the notes of the melody:

  for (int i = 0; i < length; i++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / duration[i];
    tone(8, sound[i], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
  
}