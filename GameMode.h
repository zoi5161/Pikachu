#include "Header.h"

// Navigating game mode selection
void inputGameMode(int &dirGM)
{
	halfdelay(1);

    int c = getch();
    switch(c)
    {
        case KEY_LEFT:
            dirGM = 1;
            break;
        case KEY_RIGHT:
            dirGM = 2;
            break;
        case ' ':
            dirGM = 3;
            break;
        case '\n':
            dirGM = 3;
            break;
        default:
            break;
    }
}

// Game mode background
void inputBackgroundGM(string backgroundGM[])
{
    ifstream fin;
    fin.open("BackgroundGM.txt");
    int i = 0;
    while(i <= 3)
    {
        getline(fin, backgroundGM[i], '\n');
        i++;
    }
    fin.close();
}

// Easy mode background
void inputBackgroundGMEasy(string backgroundGMEasy[])
{
    ifstream fin;
    fin.open("BackgroundGMEasy.txt");
    int i = 0;
    while(i <= 8)
    {
        getline(fin, backgroundGMEasy[i], '\n');
        i++;
    }
    fin.close();
}

// Endless mode background
void inputBackgroundGMHard(string backgroundGMHard[])
{
    ifstream fin;
    fin.open("BackgroundGMHard.txt");
    int i = 0;
    while(i <= 8)
    {
        getline(fin, backgroundGMHard[i], '\n');
        i++;
    }
    fin.close();
}

// Return button background
void inputBackgroundGMReturn(string backgroundGMReturn[])
{
    ifstream fin;
    fin.open("BackgroundGMReturn.txt");
    int i = 0;
    while(i <= 4)
    {
        getline(fin, backgroundGMReturn[i], '\n');
        i++;
    }
    fin.close();
}

// Draw game mode interface
void drawGM(int chooseGM, string backgroundGM[], string backgroundGMEasy[], string backgroundGMHard[], string backgroundReturn[], char boxGM1[], char boxGM2[])
{
    // Clear old screen
    clear();

    // Draw "GAME MODE" text
    attron(COLOR_PAIR(3));
    for(int i = passingHeightMenu; i <= passingHeightMenu + 3; i++)
        for(int j = 0; j <= 54; j++)
            mvprintw(i - 4, j + 70, "%c", backgroundGM[i-12][j]);
    attroff(COLOR_PAIR(3));

    // Choose easy mode
    if(chooseGM == 2)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 12; i <= passingHeightMenu + 20; i++)
            for(int j = 0; j <= 18; j++)
                mvprintw(i - 4, j + 61, "%c", backgroundGMEasy[i-24][j]);
        mvprintw(passingHeightMenu + 22, 68, "%s", boxGM1);
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 12; i <= passingHeightMenu + 20; i++)
            for(int j = 0; j <= 18; j++)
                mvprintw(i - 4, j + 61, "%c", backgroundGMEasy[i-24][j]);
        mvprintw(passingHeightMenu + 22, 68, "%s", boxGM1);
        attroff(COLOR_PAIR(3)); 
    }

    // Choose endless mode
    if(chooseGM == 3)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 12; i <= passingHeightMenu + 20; i++)
            for(int j = 0; j <= 18; j++)
                mvprintw(i - 4, j + 115, "%c", backgroundGMHard[i-24][j]);
        mvprintw(passingHeightMenu + 22, 121, "%s", boxGM2);
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 12; i <= passingHeightMenu + 20; i++)
            for(int j = 0; j <= 18; j++)
                mvprintw(i - 4, j + 115, "%c", backgroundGMHard[i-24][j]);
        mvprintw(passingHeightMenu + 22, 121, "%s", boxGM2);

        attroff(COLOR_PAIR(3));
    }

    // Choose return to menu
    if(chooseGM == 1)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 31; i <= passingHeightMenu + 35; i++)
            for(int j = 0; j <= 12; j++)
                mvprintw(i - 4, j + 5, "%c", backgroundReturn[i-43][j]);
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 31; i <= passingHeightMenu + 35; i++)
            for(int j = 0; j <= 12; j++)
                mvprintw(i - 4, j + 5, "%c", backgroundReturn[i-43][j]);
        attroff(COLOR_PAIR(3)); 
    }

    // Update screen
    refresh();
}

// Movement navigation in game mode selection interface
void logicGM(int &dirGM, int &chooseGM, bool &endGM, bool &endGame, bool &modeHard, bool &endMap, int &prevMode, int last)
{
    switch(dirGM)
    {
        // Left shift
        case 1:
            if(chooseGM == 2 || chooseGM == 3)
                chooseGM--;
            break;
        // Right shift
        case 2:
            if(chooseGM == 1 || chooseGM == 2)
                chooseGM++;
            break;
        // Confirm the choice
        case 3:
            if(chooseGM == 1)
            {
                chooseGM = 2;
                endGM = true;
            }
            else if(chooseGM == 2)
            {
                endGame = false;
                modeHard = false;
                if(prevMode == 0)
                    prevMode = 1;
            }
            else if(chooseGM == 3)
            {
                endMap = false;
                if(modeHard == true && last != 0)
                    endGame = false;
            }
            break;
        default:
            break;
    }
    dirGM = 0;
}