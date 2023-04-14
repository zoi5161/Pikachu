#include "Header.h"

// Navigating tutorial selection
void inputTutorial(bool &endTutorial)
{
    halfdelay(1);
    int c = getch();
    if(c == ' ')
        endTutorial = true;
}

// Tutorial background
void inputBackgroundTutorial(string backgroundTutorial[])
{
    ifstream fin;
    fin.open("BackgroundTutorial.txt");
    int i = 0;
    while(i <= 42)
    {
        getline(fin, backgroundTutorial[i], '\n');
        i++;
    }
    fin.close();
}

// Draw tutorial interface
void drawTutorial(string backgroundTutorial[])
{
    for(int i = 0; i <= 41; i++)
    {
        for(int j = 0; j <= 133; j++)
        {
            // Draw important texts
            if((i <= 3) || (i == 35 && j >= 72 && j <= 83) || i == 41)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + 5, j + 15, "%c", backgroundTutorial[i][j]);    
                attroff(COLOR_PAIR(1));        
            }
            else
            {
                attron(COLOR_PAIR(3));
                mvprintw(i + 5, j + 15, "%c", backgroundTutorial[i][j]);    
                attroff(COLOR_PAIR(3));        
            }
        }
    }
    // Update screen
    refresh();
}