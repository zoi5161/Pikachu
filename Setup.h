#include "Header.h"

void setupGame(int height, int width, int &x, int &y, int &prevX, int &prevY, int &score, int &choosePause, bool &confirm, bool &modeHard, int round, int Map, int &last, int &dir, int &hour,int &minute, int &second, int &millisec, int &totalTime,int obj[27], int randomObj, char idxObj[][widthB+2], int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int greenBlock[][widthB+2], int redBlock[][widthB+2])
{
	x = 1;
	y = 1;

    // The boxes haven't selected yet
    prevX = 200;
    prevY = 200;

    // Number of original pairs of boxes
    last = ((height+1)/5)*((width+1)/10)/2;

    dir = 0;
    hour = 0;
    millisec = 0;
    greenBlock = 0;
    redBlock = 0;
    confirm = false;
    choosePause = 1;

    // Initialize total time and score when first entering the game
    if((!modeHard && round == 1) || modeHard)
    {
        score = 0;
        totalTime = 0;
        second = 0;
    }

    // Reset time for each level 
    if(!modeHard)
    {
        if(round == 1)
            minute = 5;
        else if(round == 2)
        {
            totalTime += (4-minute)*60 + 60 - second;
            minute = 10;
            second = 0;
        }
        else if(round == 3)
        {
            totalTime += (9-minute)*60 + 60 - second;
            minute = 15;
            second = 0;
        }
    }
    else
    {
        if(Map == 1)
            minute = 5;
        else if(Map == 2)
            minute = 10;
        else if(Map == 3)
            minute = 15;
    }

    // Initialize an int array of letters
    for(int i=65; i<=90; i++)
        obj[i] = 0;

    // Randomly generate pairs of letters
    for(int i=0; i<((height+1)/5)*((width+1)/10)/2; i++)
        obj[(rand()%26)+65] += 2;
    
    // Consider the positions with the letter
    for(int i=3; i<height+2; i += 5)
        for(int j=5; j<width+2; j += 10)
        {
            // Randomly generate letters
            randomObj = (rand()%26)+65;

            // Find random letters until you find the generated one
            while(obj[randomObj] == 0)
                randomObj = (rand()%26)+65;

            // Save the letter in the position of the letter
            idxObj[i][j] = char(randomObj);

            // Save the letter int at the beginning of the cell. Simulated '~' character in BoardDemo.txt
            idxNum[i-2][j-4] = randomObj;

            // Reduce a pair of letters
            obj[randomObj]--;
        }

    for(int i=0; i<height+2; i++)
        for(int j=0; j<width+2; j++)
        {
            // The value definition is stated in the "Game.cpp" file
            // The corner position of the cell
            if(i%5 == 0 && j%10 == 0)
                idxNum[i][j] = 300;
            // The edges of the Board Game
            else if(i == 0 || i == height+1 || j == 0 || j == width+1)
                idxNum[i][j] = 301;
            // The edges of the boxes are in the Board Game
            else if(i%5 == 0 || j%10 == 0)
                idxNum[i][j] = 302;
            // The positions of the letters
            else if(i%5 == 3 && j%5 == 0 && j%10 != 0)
                idxNum[i][j] = 500;
            
            // Initialize seams in and out of the Board Game, the directional seams.
            line[i][j] = 0;
            lineEnd[i][j] = 0;
            lineOut[i][j] = 0;
        }
}

// Time operation
void runTime(int &hour, int &minute, int &second, int &millisec, bool &endGame)
{
    millisec += 10; // 1 second in machine for 0.1 second in real life
    if(millisec == 100) 
    {
        if(hour == 0 && minute == 0 && second == 0)
            endGame = true;
        else if(second == 0 && minute == 0)
        {
            hour--;
            minute = 59;
            second = 59;
        }
        else if(second == 0)
        {
            minute--;
            second = 59;
        }
        else
            second--;
        millisec = 0;
    }
}