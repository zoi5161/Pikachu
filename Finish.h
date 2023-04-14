#include "Header.h"

// Confirm exit win or lose screen
void inputFinish(bool &endFinish)
{
    halfdelay(1);

    int c = getch();
    
    if(c == '\n')
        endFinish = true;
}

// Winner background
void inputBackgroundWinner(string backgroundWinner[])
{
    ifstream fin;
    fin.open("BackgroundWinner.txt");
    int i = 0;
    while(i <= 34)
    {
        getline(fin, backgroundWinner[i], '\n');
        i++;
    }
    fin.close();
}

// Loser background
void inputBackgroundLoser(string backgroundLoser[])
{
    ifstream fin;
    fin.open("BackgroundLoser.txt");
    int i = 0;
    while(i <= 34)
    {
        getline(fin, backgroundLoser[i], '\n');
        i++;
    }
    fin.close();
}

// Draw finish game background
void drawFinish(string backgroundWinner[], string backgroundLoser[], int totalTime, int score, bool win, int minute, int second)
{
    // Clear old screen
    clear();

    for(int i = 0; i <= 34; i++)
    {
        for(int j = 0; j <= 71; j++)
        {  
            if(win)
            {
                // Draw point printing position and time printing position
                if(i == 11 && ((j >= 6 && j <= 34) || (j >= 42 && j <= 66)))
                {
                    attron(COLOR_PAIR(1));
                    if(j == 27)
                        mvprintw(i + 11, j + 50, "%02d:%02d", (totalTime + (14 - minute)*60 + 60 - second)/60, (totalTime + (14 - minute)*60 + 60 - second)%60);
                    else if(j == 59)
                        mvprintw(i + 11, j + 50, "%d", score);
                    else if(j < 27 || (j > 31 && j < 59) || j > 63)
                        mvprintw(i + 11, j + 50, "%c", backgroundWinner[i][j]);
                    attroff(COLOR_PAIR(1));
                }
                // Draw background
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(i + 11, j + 50, "%c", backgroundWinner[i][j]);
                    attroff(COLOR_PAIR(3));
                }
            }
            // Lose
            else
            {
                // Draw point printing position and time printing position
                if(i == 14 && j >= 40 && j <= 58)
                {
                    attron(COLOR_PAIR(1));
                    if(j == 53)
                        mvprintw(i + 11, j + 50, "%d", score);
                    else if(j < 53 || j >= 56)
                        mvprintw(i + 11, j + 50, "%c", backgroundLoser[i][j]);
                    attroff(COLOR_PAIR(1));
                }
                // Draw background
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(i + 11, j + 50, "%c", backgroundLoser[i][j]);
                    attroff(COLOR_PAIR(3));
                }
            }
        }
    }
    // Update screen
    refresh();
}