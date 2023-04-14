#include "Header.h"

// Pause background
void inputBackgroundPause(string backgroundPause[])
{
    ifstream fin;
    fin.open("BackgroundPause.txt");
    int i = 0;
    while(i <= 3)
    {
        getline(fin, backgroundPause[i], '\n');
        i++;
    }
    fin.close();
}

// Navigating pause selection
void inputPause(int &dirPause)
{
    halfdelay(1);

    int c = getch();
    switch(c)
    {
        case KEY_UP:
            dirPause = 1;
            break;
        case KEY_DOWN:
            dirPause = 2;
            break;
        case ' ':
            dirPause = 3;
            break;
        case '\n':
            dirPause = 3;
            break;
        default:
            break;
    }
}

// Draw pause selection interface
void drawPause(int choosePause, string backgroundPause[], char boxExit[], char boxResume[])
{
    // Clear old screen
    clear();

    // Draw "PAUSE" text
    attron(COLOR_PAIR(3));
    for(int i = passingHeightMenu; i <= passingHeightMenu + 3; i++)
        for(int j = 0; j <= 26; j++)
            mvprintw(i, j + 80, "%c", backgroundPause[i-12][j]);
    attroff(COLOR_PAIR(3));
    
    // Choose resume the game
    if(choosePause == 1)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 8; i <=passingHeightMenu + 10; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 9 && (j == 5 || j == 22))
                    mvprintw(i,  j + 80, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 9)
                    mvprintw(i,  j + 80, "-");
                else if(j == 11 && i == passingHeightMenu + 9)
                    mvprintw(i,  j + 80, "%s", boxResume);
            }
        }
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 8; i <=passingHeightMenu + 10; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 9 && (j == 5 || j == 22))
                    mvprintw(i,  j + 80, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 9)
                    mvprintw(i,  j + 80, "-");
                else if(j == 11 && i == passingHeightMenu + 9)
                    mvprintw(i,  j + 80, "%s", boxResume);
            }
        }
        attroff(COLOR_PAIR(3));
    }

    // Choose exit the game
    if(choosePause == 2)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 13; i <=passingHeightMenu + 15; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 14 && (j == 5 || j == 22))
                    mvprintw(i,  j + 80, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 14)
                    mvprintw(i,  j + 80, "-");
                else if(j == 12 && i == passingHeightMenu + 14)
                    mvprintw(i,  j + 80, "%s", boxExit);
            }
        }
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 13; i <=passingHeightMenu + 15; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 14 && (j == 5 || j == 22))
                    mvprintw(i,  j + 80, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 14)
                    mvprintw(i,  j + 80, "-");
                else if(j == 12 && i == passingHeightMenu + 14)
                    mvprintw(i,  j + 80, "%s", boxExit);
            }
        }
        attroff(COLOR_PAIR(3));
    }
    // Update screen
    refresh();
}

void logicPause(int &dirPause, int &choosePause, bool &endPause, bool &endGame)
{
    switch(dirPause)
    {
        // Up shift
        case 1:
            if(choosePause == 1)
                choosePause = 2;
            else
                choosePause--;
            break;
        // Down shift
        case 2:
            if(choosePause == 2)
                choosePause = 1;
            else
                choosePause++;
            break;
        // Confirm the choice
        case 3:
            // Exit to game mode selection interface
            if(choosePause == 2)
            {
                endPause = true;
                endGame = true;
            }
            // Resume the game
            else
                endPause = true;
            break;
        default:
            break;
    }
    dirPause = 0;
}