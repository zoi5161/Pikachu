#include "Header.h"

// Navigating map selection
void inputMap(int &dirMap)
{
	halfdelay(1);

    int c = getch();
    switch(c)
    {
        case KEY_LEFT:
            dirMap = 1;
            break;
        case KEY_RIGHT:
            dirMap = 2;
            break;
        case ' ':
            dirMap = 3;
            break;
        case '\n':
            dirMap = 3;
            break;
        default:
            break;
    }
}

// Small game simulation background
void inputMapS(string backgroundMapS[])
{
    ifstream fin;
    fin.open("BackgroundMapS.txt");
    int i = 0;
    while(i <= 7)
    {
        getline(fin, backgroundMapS[i], '\n');
        i++;
    }
    fin.close();
}

// Medium game simulation background
void inputMapM(string backgroundMapM[])
{
    ifstream fin;
    fin.open("BackgroundMapM.txt");
    int i = 0;
    while(i <= 9)
    {
        getline(fin, backgroundMapM[i], '\n');
        i++;
    }
    fin.close();
}

// Big game simulation background
void inputMapB(string backgroundMapB[])
{
    ifstream fin;
    fin.open("BackgroundMapB.txt");
    int i = 0;
    while(i <= 11)
    {
        getline(fin, backgroundMapB[i], '\n');
        i++;
    }
    fin.close();
}

// "MAP" text
void inputTextMap(string backgroundMap[])
{
    ifstream fin;
    fin.open("BackgroundMap.txt");
    int i = 0;
    while(i <= 3)
    {
        getline(fin, backgroundMap[i], '\n');
        i++;
    }
    fin.close();
}

// Draw map interface
void drawMap(int chooseMap, string backgroundMap[], string backgroundMapS[], string backgroundMapM[], string backgroundMapB[], string backgroundGMReturn[])
{
    // Clear old screen
    clear();

    // Draw "MAP" text
    attron(COLOR_PAIR(3));
    for(int i = passingHeightMenu; i <= passingHeightMenu + 3; i++)
        for(int j = 0; j <= 17; j++)
            mvprintw(i - 4, j + 82, "%c", backgroundMap[i-12][j]);
    attroff(COLOR_PAIR(3));

    // Choose map small
    if(chooseMap == 2)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 14; i <= passingHeightMenu + 21; i++)
            for(int j = 0; j <= 17; j++)
                mvprintw(i - 4, j + 40, "%c", backgroundMapS[i-26][j]);
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 14; i <= passingHeightMenu + 21; i++)
            for(int j = 0; j <= 17; j++)
                mvprintw(i - 4, j + 40, "%c", backgroundMapS[i-26][j]);
        attroff(COLOR_PAIR(3)); 
    }

    // Choose map medium
    if(chooseMap == 3)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 13; i <= passingHeightMenu + 22; i++)
            for(int j = 0; j <= 22; j++)
                mvprintw(i - 4, j + 78, "%c", backgroundMapM[i-25][j]);
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 13; i <= passingHeightMenu + 22; i++)
            for(int j = 0; j <= 22; j++)
                mvprintw(i - 4, j + 78, "%c", backgroundMapM[i-25][j]);
        attroff(COLOR_PAIR(3));
    }

    // Choose map big
    if(chooseMap == 4)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 12; i <= passingHeightMenu + 23; i++)
            for(int j = 0; j <= 37; j++)
                mvprintw(i - 4, j + 120, "%c", backgroundMapB[i-24][j]);
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 12; i <= passingHeightMenu + 23; i++)
            for(int j = 0; j <= 37; j++)
                mvprintw(i - 4, j + 120, "%c", backgroundMapB[i-24][j]);
        attroff(COLOR_PAIR(3));
    }

    // Choose return to game mode selection interface
    if(chooseMap == 1)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 31; i <= passingHeightMenu + 35; i++)
            for(int j = 0; j <= 12; j++)
                mvprintw(i - 4, j + 5, "%c", backgroundGMReturn[i-43][j]);
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 31; i <= passingHeightMenu + 35; i++)
            for(int j = 0; j <= 12; j++)
                mvprintw(i - 4, j + 5, "%c", backgroundGMReturn[i-43][j]);
        attroff(COLOR_PAIR(3));
    }
    // Update screen
    refresh();
}

// Navigate movement in the map selection interface
void logicMap(int &dirMap, int &chooseMap, bool &endMap, bool &endGame, bool &modeHard, int &Map, int &prevMode)
{
    switch(dirMap)
    {
        // Left shift
        case 1:
            if(chooseMap == 2 || chooseMap == 3 || chooseMap == 4)
                chooseMap--;
            break;
        // Right shift
        case 2:
            if(chooseMap == 1 || chooseMap == 2 || chooseMap == 3)
                chooseMap++;
            break;
        // Confirm the choice
        case 3:
            // Confirm return to game mode selection interface
            if(chooseMap == 1)
            {
                chooseMap = 2;
                endMap = true;
            }
            else
            {
                modeHard = true;
                if(prevMode == 0)
                    prevMode = 2;
                endGame = false;
                endMap = true;
                modeHard = true;
                Map = chooseMap - 1;
            }
            break;
        default:
            break;
    }
    dirMap = 0;
}