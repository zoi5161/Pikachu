#include "Header.h"

void soundPlay(bool &soundPl) 
{
    PlaySound(TEXT("playGame.wav"), NULL, SND_FILENAME | SND_ASYNC);
    soundPl = 0;
}

// This sound plays when opening menu
void soundMenu(bool &soundMN) 
{
    PlaySound(TEXT("Menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
    soundMN = 0;
}

// This sound plays that plays at the end of a level
void soundFinish(bool &soundFi) 
{
    PlaySound(TEXT("Finish.wav"), NULL, SND_FILENAME | SND_ASYNC);
    soundFi = 0;
}

// This sound plays when deleting 2 boxes
void soundDelete(bool &soundDele) 
{
    PlaySound(TEXT("delete.wav"), NULL, SND_FILENAME | SND_ASYNC);
    soundDele = 0;
}

// This sound plays when 2 cells are selected wrong
void soundError(bool &soundErr) 
{
    PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
    soundErr = 0;
}