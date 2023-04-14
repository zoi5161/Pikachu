#include "Header.h"

// Warn background
void inputBackgroundWarn(string backgroundWarn[])
{
    ifstream fin;
    fin.open("BackgroundWarn.txt");
    int i = 0;
    while(i <= 9)
    {
        getline(fin, backgroundWarn[i], '\n');
        i++;
    }
    fin.close();
}

// Next button background
void inputBackgroundNext(string backgroundNext[])
{
    ifstream fin;
    fin.open("BackgroundNext.txt");
    int i = 0;
    while(i <= 4)
    {
        getline(fin, backgroundNext[i], '\n');
        i++;
    }
    fin.close();
}

// Navigating warn selection
void inputWarn(int &dirWarn)
{
    halfdelay(1);

    int c = getch();
    switch(c)
    {
        case KEY_LEFT:
            dirWarn = 1;
            break;
        case KEY_RIGHT:
            dirWarn = 2;
            break;
        case ' ':
            dirWarn = 3;
            break;
        case '\n':
            dirWarn = 3;
            break;
        default:
            break;
    }
}

// Draw warn interface
void drawWarn(int chooseWarn, string backgroundWarn[], string backgroundNext[], string backgroundReturn[])
{
    // Clear old screen
    clear();

    // Draw "WARNING" text
    attron(COLOR_PAIR(1));
    for(int i = passingHeightMenu; i <= passingHeightMenu + 9; i++)
        for(int j = 0; j <= 43; j++)
            mvprintw(i, j + 75, "%c", backgroundWarn[i-12][j]);
    attroff(COLOR_PAIR(1));

    // Choose return to the previous interface
    if(chooseWarn == 1)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 31; i <= passingHeightMenu + 35; i++)
            for(int j = 0; j <= 12; j++)
                mvprintw(i, j + 5, "%c", backgroundReturn[i-43][j]);
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 31; i <= passingHeightMenu + 35; i++)
            for(int j = 0; j <= 12; j++)
                mvprintw(i, j + 5, "%c", backgroundReturn[i-43][j]);
        attroff(COLOR_PAIR(3)); 
    }

    // Choose next (Player want to continue)
    if(chooseWarn == 2)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 31; i <= passingHeightMenu + 35; i++)
            for(int j = 0; j <= 12; j++)
                mvprintw(i, j + 170, "%c", backgroundNext[i-43][j]);
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 31; i <= passingHeightMenu + 35; i++)
            for(int j = 0; j <= 12; j++)
                mvprintw(i, j + 170, "%c", backgroundNext[i-43][j]);
        attroff(COLOR_PAIR(3)); 
    }
    // Update screen
    refresh();
}

// Movement navigation in warn selection interface
void logicWarn(int &dirWarn, int &chooseWarn, bool &endWarn, bool &modeHard, int &prevMode, bool &endGame, bool &endMap, int &last, int &round)
{
    switch(dirWarn)
    {
        // Left shift
        case 1:
            chooseWarn = 1;
            break;
        // Right shift
        case 2:
            chooseWarn = 2;
            break;
        // Confirm the choice
        case 3:
            endWarn = true;
            // Return to the previous interface
            if(chooseWarn == 1)
            {
                endGame = true;
                endMap = true;
                if(modeHard)
                    modeHard = false;
                else 
                    modeHard = true;
            }
            // Choose next
            else
            {
                last = 0;
                if(modeHard)
                {
                    prevMode = 2;
                    round = 1;
                }
                else 
                    prevMode = 1;
            }
            break;
        default:
            break;
    }
    dirWarn = 0;
}

// Movement navigation in warn selection interface if you choose new game
void logicWarnNewGame(int &dirWarn, int &chooseWarnNewGame, bool &newGame, int &prevMode, int &last, int &round, bool &endGM)
{
    switch(dirWarn)
    {
        // Left shift
        case 1:
            chooseWarnNewGame = 1;
            break;
        // Right shift
        case 2:
            chooseWarnNewGame = 2;
            break;
        // Confirm the choice
        case 3:
            newGame = true;
            // Confirm new game
            if(chooseWarnNewGame == 2)
            {
                endGM = false;
                prevMode = 0;
                round = 1;
                last = 0;
            }
            break;
        default:
            break;
    }
    dirWarn = 0;
}