#include "highscore.h"
#include "EEPROM.h"

// Receives a score, and checks if it is in the top 4 and places it accordingly
// 50, 40, 23, 11
// score = 45
// index = 1
// test = 3
// 3 > 1
// topScores[test] = topScores[test-1];
// 11 = 23
// 50 40 23 23
// test--
// 2 > 1
// topScores[test] = topScores[test-1];
// 23 = 40
// 50 40 40 23
// test--
// 1 > 1
// false
// topScores[index] = score;
// 40 = 45
// 50, 45, 40, 23
void CheckTopScore(byte score)
{
    int index = -1;

    for(int i = 0; i<4; i++){
        if(topScores[i] <= score){
            index = i;
            break;
        }
    }

    if (index == -1)
        return;

    int reversingIndex = 3;

    while (reversingIndex > index)
    {
        topScores[reversingIndex] = topScores[reversingIndex-1];
        reversingIndex--;
    }

    topScores[index] = score;

    SaveScores();
}

// Writes a score to ROM addresses 0-3 are "top 1-4"
// Receives a score and an address
void WriteToROM(byte score, byte address)
{
    EEPROM.put(address, score);
}

// Read a value from an address and return it
byte ReadFromROM(byte address)
{
    return EEPROM.read(address);
}

// Update the array of the top scores
void GetTopScores()
{
    for (int i=0; i < 4; i++)
    {
      topScores[i] = ReadFromROM(i);
    }
}

void SaveScores()
{
    for (int i=0; i < 4; i++)
    {
      WriteToROM(topScores[i], i);
    }

}
