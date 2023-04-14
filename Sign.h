#include "Header.h"

// Check the correct password
bool checkPass(char user[], char pass[])
{
    char userClone[20], passClone[20];
    ifstream fin("account.bin", ios::binary);
    // Move the cursor to the beginning of the file
    fin.seekg(0, ios::beg);
    while(!fin.eof())
    {
        fin.read(userClone, 20);
        fin.read(passClone, 20);
        if(strcmp(userClone, user) == 0 && strcmp(passClone, pass) == 0)
            return true;
    }
    fin.close();
    return false;
}

// Check created account
bool availableAccount(char user[])
{
    char userClone[20];
    ifstream fin("account.bin", ios::binary);
    // Move the cursor to the beginning of the file
    fin.seekg(0, ios::beg);
    while(!fin.eof())
    {
        fin.read(userClone, 20);
        if(strcmp(userClone, user) == 0)
            return true;
    }
    fin.close();
    return false;
}

// Create Account
void createAccount(char user[], char pass[])
{
    ofstream fout("account.bin", ios::binary | ios::app);
    fout.write(user, 20);
    fout.write(pass, 20);
    fout.close();
}

// Navigating sign selection
void inputSign(char user[], char pass[], bool &endUser, bool &endPass, bool &endSign, bool &endSeen, bool &endGM, bool &warnAcc, bool &signUp, int &chooseMenu)
{
    halfdelay(1);
    
    int ch;
    char c;

    ch = getch();
    c = char(ch);

    // Return to menu
    if(ch == '=')
    {
        for(int i = 0; i < strlen(user); i++)
            user[i] = '\0';
        for(int i = 0; i < strlen(pass); i++)
            pass[i] = '\0';   
        endUser = false;
        endPass = true;
        endSign = true;
        endSeen = true;
        warnAcc = false;  
        signUp = false; 
    }

    // Tab to see password
    if(ch == '\t')
    {
        if(endSeen)
            endSeen = false;
        else 
            endSeen = true;
    }

    // After enter password
    if(endUser && endPass)
    {
        // Account successfully created then go to game mode
        if((!signUp && checkPass(user, pass)) || signUp) // 
            endSign = true;
        // Account login failed then input password again
        else
            endPass = false;
    }

    // Input password. Initially, the "endPass" variable equal false
    if(!endPass)
    {
        // In the registration interface, if the account is already available, the game will notify you with a warning
        if(availableAccount(user) && signUp)
            warnAcc = true;
        else if(signUp)
            warnAcc = false;
        else if(availableAccount(user) && !signUp)
            warnAcc = false;
        // In the login interface, if the account is already available, the game will notify you with a warning
        else if(!signUp)
            warnAcc = true;
        
        // Switch to the registration interface
        if(!signUp && ch == '\n' && warnAcc)
        {
            signUp = true;
            endPass = true;
            endUser = false;
            chooseMenu = 1;
        }

        // Move the cursor to the username input box
        if(ch == KEY_UP)
        {
            endPass = true;
            endUser = false;
        }
        // Keep the cursor in the password box
        else
        {
            // Enter a letter
            if(((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')) && strlen(pass) < 18)
            {
                pass[strlen(pass)] = c;
                pass[strlen(pass)] = '\0';
            }
            // Delete a letter
            else if(strlen(pass) > 0 && ch == '-') // Replace '-' for backspace key because the backspace key in the ascii encoding has a different value on some machines.
                pass[strlen(pass)-1] = '\0';
            // Create an account if the game doesn't give a warning
            else if(ch == '\n' && strlen(pass) > 0 && !warnAcc)
            {
                endPass = true;
                endGM = false;
                if(signUp)
                    createAccount(user, pass);
                return;
            }
        }
    }
    
    // Input username. Initially, the "endUser" variable equal false
    if(!endUser)
    {   
        // If the cursor is in the username box, the game will not notify you with a warning
        warnAcc = false;
        // Move the cursor to the password input box
        if((ch == KEY_DOWN || ch == '\n') && strlen(user) > 0)
        {
            endUser = true;
            endPass = false;
        }
        // Keep the cursor in the username box
        else
        {
            // Enter a letter
            if(((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')) && strlen(user) < 18)
            {
                user[strlen(user)] = c;
                user[strlen(user)] = '\0';
            }
            // Delete a letter
            else if(strlen(user) > 0 && ch == '-')
                user[strlen(user)-1] = '\0';
        }
    }
}

// Sign background
void inputBackgroundSign(string backgroundSign[], string s)
{
    ifstream fin;
    fin.open(s);
    int i = 0;
    while(i <= 36)
    {
        getline(fin, backgroundSign[i], '\n');
        i++;
    }
    fin.close();
}

// Draw sign interface
void drawSign(string backgroundSign[], char user[], char pass[], bool endSeen, bool &warnAcc, bool &signUp)
{
    // Clear old screen
    clear();

    for(int i = 0; i <= 36; i++)
        for(int j = 0; j <= 184; j++)
        {
            // Notice username already used
            if(warnAcc && i == 29 && j >= 59 && j <= 84 && signUp)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(1));
            }
            // If there is no warning message, the game prints a space in the place of the warning
            else if(!warnAcc && (i == 28 || i == 29) && j >= 48 && j <= 99 && signUp)
            {
                attron(COLOR_PAIR(9));
                mvprintw(i + 5, j + 20, " ");
                attron(COLOR_PAIR(9));
            }
            // Notice invalid username
            else if(warnAcc && (i == 28 || i == 29) && j >= 48 && j <= 99 && !signUp)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(1));
            }
            // If there is no warning message, the game prints a space in the place of the warning
            else if(!warnAcc && (i == 28 || i == 29) && j >= 48 && j <= 99 && !signUp)
            {
                attron(COLOR_PAIR(9));
                mvprintw(i + 5, j + 20, " ");
                attron(COLOR_PAIR(9));
            }
            // Draw the entered username
            else if(i == 22 && j >= 67 && j < (int)(67 + strlen(user)))
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + 5, j + 20, "%c", user[j-67]);
                attron(COLOR_PAIR(1));
            }
            // Draw the entered password
            else if(i == 24 && j >= 67 && j < (int)(67 + strlen(pass)))
            {
                // If the password view (Tab) is not enabled, the password will be displayed as *
                if(endSeen)
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(i + 5, j + 20, "*");
                    attron(COLOR_PAIR(1));
                }
                // Otherwise the password will be displayed
                else
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(i + 5, j + 20, "%c", pass[j-67]);
                    attron(COLOR_PAIR(1));
                }
            }
            // Draw the password view icon
            else if(i >= 23 && i <= 25 && j >= 91 && j <= 98)
            {
                if(endSeen)
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                    attron(COLOR_PAIR(3));
                }
                else
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                    attron(COLOR_PAIR(1));
                }
            }
            // Draw password box
            else if(i >= 21 && i <= 25 && j >= 55 && j <= 89)
            {
                attron(COLOR_PAIR(3));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(3));
            }
            // Draw username box
            else if(i >= 10 && i <= 15 && j >= 37 && j <= 108)
            {
                attron(COLOR_PAIR(6));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(6));
            }
            // Draw instructions to remove characters and return menu
            else if(i >= 34)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(1));
            }
            // Draw background
            else
            {
                attron(COLOR_PAIR(2));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(2));
            }
        }
    // Update screen
    refresh();
}