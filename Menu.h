#include "Header.h"

// Setting color
void setupColor()
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_WHITE);
    init_pair(9, COLOR_BLACK, COLOR_BLACK);
    init_pair(10, COLOR_RED, COLOR_RED);
    init_pair(11, COLOR_GREEN, COLOR_GREEN);
    init_pair(12, COLOR_RED, COLOR_WHITE);
    init_pair(13, COLOR_BLACK, COLOR_WHITE);
    init_pair(14, COLOR_YELLOW, COLOR_WHITE);
    init_pair(15, COLOR_GREEN, COLOR_WHITE);
}

// Navigating menu selection
void inputMenu(int &hz, int &dirMenu)
{
	keypad(stdscr, true);
	halfdelay(1);

    int c = getch();
    switch(c)
    {
        case KEY_UP:
        {
            hz++;
            dirMenu = 1;
            break;
        }
        case KEY_DOWN:
        {
            hz++;
            dirMenu = 2;
            break;
        }
        case '\n':
        {
            dirMenu = 3;
            break;
        }
        case ' ':
        {
            dirMenu = 3;
            break;
        }
        default:
            break;
    }
}

// Menu 1 background
void inputBackgroundMenu1(string backgroundMenu1[])
{
    ifstream fin;
    fin.open("BackgroundMenu1.txt");
    int i = 0;
    while(i<=40)
    {
        getline(fin, backgroundMenu1[i], '\n');
        i++;
    }
    fin.close();
}

// Menu 2 background
void inputBackgroundMenu2(string backgroundMenu2[])
{
    ifstream fin;
    fin.open("BackgroundMenu2.txt");
    int i = 0;
    while(i<=38)
    {
        getline(fin, backgroundMenu2[i], '\n');
        i++;
    }
    fin.close();
}

// Draw menu interface
void drawMenu(int &hz, int &chooseMenu, char box1[], char box2[], char box3[], char box4[], string backgroundMenu1[], string backgroundMenu2[])
{
    // Clear old screen
    clear();
    
    // Choose "SIGN UP" or "NEW GAME"
    if(chooseMenu == 1)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 5; i <= passingHeightMenu + 5 + 2; i++)
        {
            for(int j = 5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 5 + 1 && (j == 5 || j == 22))
                    mvprintw(i, j, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 5 + 1)
                    mvprintw(i, j, "-");
                else if(j == 11 && i == passingHeightMenu + 5 + 1)
                    mvprintw(i, j, "%s", box1);
            }
        }
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 5; i <= passingHeightMenu + 5 + 2; i++)
        {
            for(int j = 5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 5 + 1 && (j == 5 || j == 22))
                    mvprintw(i, j, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 5 + 1)
                    mvprintw(i, j, "-");
                else if(j == 11 && i == passingHeightMenu + 5 + 1)
                    mvprintw(i, j, "%s", box1);
            }
        }
        attroff(COLOR_PAIR(3));
    }

    // Choose "SIGN IN" or "CONTINUE"
    if(chooseMenu == 2)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 5 + 5; i <= passingHeightMenu + 5 + 7; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 5 + 6 && (j == 5 || j == 22))
                    mvprintw(i, j, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 5 + 6)
                    mvprintw(i, j, "-");
                else if(j == 11 && i == passingHeightMenu + 5 + 6)
                    mvprintw(i, j, "%s", box2);
            }
        }
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 5 + 5; i <= passingHeightMenu + 5 + 7; i++)
        {
            for(int j = 5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 5 + 6 && (j == 5 || j == 22))
                    mvprintw(i, j, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 5 + 6)
                    mvprintw(i, j, "-");
                else if(j == 11 && i == passingHeightMenu + 5 + 6)
                    mvprintw(i, j, "%s", box2);
            }
        }
        attroff(COLOR_PAIR(3));
    }

    // Choose tutorial
    if(chooseMenu == 3)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 5 + 10; i<= passingHeightMenu + 5 + 12; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 5 + 11 && (j == 5 || j == 22))
                    mvprintw(i, j, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 5 + 11)
                    mvprintw(i, j, "-");
                else if(j == 10 && i == passingHeightMenu + 5 + 11)
                    mvprintw(i, j, "%s", box3);
            }
        }
        attroff(COLOR_PAIR(1));
    }
    else
    {       
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 5 + 10; i<= passingHeightMenu + 5 + 12; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 5 + 11 && (j == 5 || j == 22))
                    mvprintw(i, j, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 5 + 11)
                    mvprintw(i, j, "-");
                else if(j == 10 && i == passingHeightMenu + 5 + 11)
                    mvprintw(i, j, "%s", box3);
            }
        }
        attroff(COLOR_PAIR(3));
    }

    // Choose exit
    if(chooseMenu == 4)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 5 + 15; i<= passingHeightMenu + 5 + 17; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 5 + 16 && (j == 5 || j == 22))
                    mvprintw(i, j, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 5 + 16)
                    mvprintw(i, j, "-");
                else if(j == 12 && i == passingHeightMenu + 5 + 16)
                    mvprintw(i, j, "%s", box4);
            }
        }
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 5 + 15; i<= passingHeightMenu + 5 + 17; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 5 + 16 && (j == 5 || j == 22))
                    mvprintw(i, j, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 5 + 16)
                    mvprintw(i, j, "-");
                else if(j == 12 && i == passingHeightMenu + 5 + 16)
                    mvprintw(i, j, "%s", box4);
            }
        }
        attroff(COLOR_PAIR(3));
    }
    
    // Draw background menu 1
    if(hz%2 == 0)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu - 4; i <= 48; i++)
            for(int j = 0; j <= 69; j++)
                mvprintw(i - 4, j + 80, "%c", backgroundMenu1[i - 8][j]);
        attroff(COLOR_PAIR(1));
    }
    // Draw background menu 2
    else
    {
        attron(COLOR_PAIR(6));
        for(int i = passingHeightMenu - 3; i <= 47; i++)
            for(int j = 0; j <= 127; j++)
                mvprintw(i - 4, j + 40, "%c", backgroundMenu2 [i - 9][j]);
        attroff(COLOR_PAIR(6));

        attron(COLOR_PAIR(9));
        for(int i = 50; i <= 60; i++)
            for(int j = 0; j <= 160; j++)
                mvprintw(i, j, " ");
        attroff(COLOR_PAIR(9));
    } 
    // Update screen
    refresh();
}

// Navigate movement in the menu selection interface
void logicMenu(int &chooseMenu, int &dirMenu, bool &endMenu, bool &endGM, bool &played, bool &endWarn, bool &newGame, bool &endSign, bool &endTutorial, bool &signUp)
{
    switch(dirMenu)
    {
        // Up shift
        case 1:
        {    
            if(chooseMenu == 1)
                chooseMenu = 4;
            else
                chooseMenu--;
            break;
        }
        // Down shift
        case 2:
        {
            if(chooseMenu == 4)
                chooseMenu = 1;
            else
                chooseMenu++;
            break;
        }
        // Confirm the choice
        case 3:
        {
            // Have played
            if(played)
            {
                // Choose new game
                if(chooseMenu == 1)
                {
                    endWarn = false;
                    newGame = false;
                }
                // Choose continue
                else if(chooseMenu == 2)
                    endGM = false;
            }
            // Haven't played yet
            else
            {
                // Choose sign
                if(chooseMenu == 1 || chooseMenu == 2)
                    endSign = false;
                // Choose sign up. Initially, "signUp" variable equal false.
                if(chooseMenu == 1)
                    signUp = true;
            }
            // Choose tutorial
            if(chooseMenu == 3)
            {
                // Clear old screen
                clear();
                endTutorial = false;
            }
            // Choose exit
            if(chooseMenu == 4)
                endMenu = true;
            break;
        }
        default:
            break;
    }
    dirMenu = 0;
}