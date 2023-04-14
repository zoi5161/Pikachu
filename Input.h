#include "Header.h"

// Navigating in-game box 
void input(int &dir)
{
	halfdelay(1);

    int c = getch();
    switch(c)
    {
        case KEY_LEFT:
            dir = 1;
            break;
        case KEY_RIGHT:
            dir = 2;
            break;
        case KEY_UP:
            dir = 3;
            break;
        case KEY_DOWN:
            dir = 4;
            break;
        case ' ':
            dir = 5;
            break;
        case 'r':
            dir = 6;
            break;
        case 'h':
            dir = 7;
            break;
        case 'q':
            dir = 8;
            break;
        case 'p':
            dir = 9;
            break;
        case '\n':
            dir = 5;
            break;
        default:
            break;
    }
}

// Small game background
void backgroundSmall(string backgroundGame[]) // Height = 4*5-1, Width = 8*10-1
{
    std::ifstream fin;
    fin.open("backgroundSmall.txt");
    int i = 0;
    while(i<=20)
    {
        getline(fin, backgroundGame[i], '\n');
        i++;
    }
    fin.close();
}

// Medium game background
void backgroundMedium(string backgroundGame[]) // Height = 8*5-1, Width = 8*10-1
{
    std::ifstream fin;
    fin.open("backgroundMedium.txt");
    int i = 0;
    while(i<=40)
    {
        getline(fin, backgroundGame[i], '\n');
        i++;
    }
    fin.close();
}

// Big game background
void backgroundBig(string backgroundGame[]) // Height = 8*5-1, Width = 16*10-1
{
    std::ifstream fin;
    fin.open("backgroundBig.txt");
    int i = 0;
    while(i<=80)
    {
        getline(fin, backgroundGame[i], '\n');
        i++;
    }
    fin.close();
}