#include "Header.h"

void draw(int height, int width, int passingHeight, int passingWidth, int x, int y, int prevX, int prevY, int hour, int minute, int second, int score, int last, int round, bool modeHard, char boxConfirm[], string backgroundGame[],char idxObj[][widthB+2], int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int lineHelp[][widthB+2], int resetNum[][widthB+2], int resetLine[][widthB+2], int resetLineOut[][widthB+3], int resetLineEnd[][widthB+2], int greenBlock[][widthB+2], int redBlock[][widthB+2])
{
    // Clear old screen
    clear();
    
    // Draw the time and the score at the top of the Board Game
    attron(COLOR_PAIR(3));
    printw("Time: %02d:%02d:%02d           Score: %d", hour, minute, second, score);
    attroff(COLOR_PAIR(3));

    // If you use Mac OS then use the row below
    // std::this_thread::sleep_for(std::chrono::milliseconds(1)); // The program will stop executing for 1 millisecond (1/1000 second).

    // If you use Window then use the row below
    Sleep(1); // The program will stop executing for 1 millisecond (1/1000 second).
    
    for(int i=0; i<height+2; i++)
    {
        for(int j=0; j<width+2; j++)
        {
            // Draw confirmation table
            if(last == 0)
            {
                attron(COLOR_PAIR(1));
                for(int u = 0; u <= 2; u++)
                {
                    for(int v = 0; v <= 48; v++)
                    {
                        if((u == 0 || u == 2) && v != 0 && v != 48)
                            mvprintw(u + passingHeight + height + 6, v + 71, "-");
                        else if((v == 0 || v == 48) && u != 0 && u != 2)
                            mvprintw(u + passingHeight + height + 6, v + 71, "|");
                        else if(u == 1 && v == 6)
                            mvprintw(u + passingHeight + height + 6, v + 71, "%s", boxConfirm);
                    }
                }
                attroff(COLOR_PAIR(1));
            }

            // Draw a seam if it is outside the board
            if(lineOut[i][j] != 0 && i == 0)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + passingHeight - 1, j + passingWidth +1, "-");
                attroff(COLOR_PAIR(1));
                lineOut[i][j]--;
            }
            else if(lineOut[i][j] != 0 && i == height+1)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + passingHeight + 1, j + passingWidth +1, "-");
                attroff(COLOR_PAIR(1));
                lineOut[i][j]--;
            }

            if(lineOut[i][j] != 0 && j == 0)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + passingHeight, j + passingWidth - 1, "|");
                attroff(COLOR_PAIR(1));
                lineOut[i][j]--;
            }
            else if(lineOut[i][j] != 0 && j == width+1)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + passingHeight, j + passingWidth + 1, "|");
                attroff(COLOR_PAIR(1));
                lineOut[i][j]--;
            }

            // Draw a seam in the board
            if(line[i][j] != 0 && (i%5 == 3 ||  j%10 == 0) ) // Draw horizontal seams
            {
                attron(COLOR_PAIR(1));
                if(lineEnd[i][j] == 3)
                    mvprintw(i + passingHeight, j + passingWidth, ">");
                else if(lineEnd[i][j] == 4)
                    mvprintw(i + passingHeight, j + passingWidth, "<");
                else
                {
                    if(line[i-1][j] == 1 || line[i+1][j] == 1)
                        mvprintw(i + passingHeight, j + passingWidth, "|");
                    else
                        mvprintw(i + passingHeight, j + passingWidth, "-");
                }
                attroff(COLOR_PAIR(1));       
                line[i][j]--;
                if(line[i][j] == 0)
                    lineEnd[i][j] = 0;   
            }
            else if(line[i][j] != 0 && (j%5 == 0 || (i%5 == 0))) // Draw vertical seams
            {
                attron(COLOR_PAIR(1));
                if(lineEnd[i][j] == 1)
                    mvprintw(i + passingHeight, j + passingWidth, "^");
                else if(lineEnd[i][j] == 2)
                    mvprintw(i + passingHeight, j + passingWidth, "v");
                else
                {
                    if(line[i][j-1] == 1 || line[i][j+1] == 1)
                        mvprintw(i + passingHeight, j + passingWidth, "-");
                    else
                        mvprintw(i + passingHeight, j + passingWidth, "|");
                }
                attroff(COLOR_PAIR(1));       
                line[i][j]--;
                if(line[i][j] == 0)
                    lineEnd[i][j] = 0;         
            }
             // Draw the correct box
            else if(greenBlock[i][j] != 0)
            {
                attron(COLOR_PAIR(11));
                mvprintw(i + passingHeight, j + passingWidth, " ");
                attroff(COLOR_PAIR(11));
                greenBlock[i][j]--;
            }
            // Draw the wrong selection box
            else if(redBlock[i][j] != 0)
            {
                attron(COLOR_PAIR(10));
                mvprintw(i + passingHeight, j + passingWidth, " ");
                attroff(COLOR_PAIR(10));
                redBlock[i][j]--;
            }
            // Draw an empty box at the current position
            else if(j >= x && j - x <= 9 && i >= y && i - y <= 4 && idxNum[i][j] == 300)
            {
                attron(COLOR_PAIR(8));
                mvprintw(i + passingHeight, j + passingWidth, " ");
                attroff(COLOR_PAIR(8));
            }
            // Draw the corner position of the cell
            else if((idxNum[i][j] == 300 || (i%5 == 0 && j%10 == 0)))
            {
                // If the letter isn't lost
                if(i%5 == 0 && j%10 == 0 && ((j == 0 && idxNum[i][j+1] != 300) || (j == width + 1 && idxNum[i][j-1] != 300) || idxNum[i][j+1] != 300))
                {
                    // If it is the current location, that position will be white
                    if((j >= x && j - x <= 9 && i >= y && i - y <= 4) || (j >= prevX && j - prevX <= 9 && i >= prevY && i - prevY <= 4))
                    {
                        attron(COLOR_PAIR(8));
                        mvprintw(i + passingHeight, j + passingWidth, " ");
                        attroff(COLOR_PAIR(8));
                    }
                    // If it's not the current location, that position will be black
                    else
                    {
                        attron(COLOR_PAIR(9));
                        mvprintw(i + passingHeight, j + passingWidth, " ");
                        attroff(COLOR_PAIR(9));
                    }
                }
                // If the letter is not lost, that position will be background Game
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(i + passingHeight, j + passingWidth, "%c", backgroundGame[i][j]);
                    attroff(COLOR_PAIR(3));
                }
            }
            // Feature 2: Hidden Squares
            // In hard mode, the crosswords will be hidden, only the selected and current boxes will show the letters
            else if(j%5 == 0 && j%10 != 0 &&  i%5 == 3 && idxNum[i][j] != 300 && modeHard)
            {
                if((j >= x && j - x <= 9 && i >= y && i - y <= 4) || (j >= prevX && j - prevX <= 9 && i >= prevY && i - prevY <= 4))
                {
                    attron(COLOR_PAIR((int)idxObj[i][j] % 8));
                    mvprintw(i + passingHeight, j + passingWidth, "%c", idxObj[i][j]);
                    attroff(COLOR_PAIR((int)idxObj[i][j] % 8));
                }
                else
                {
                    attron(COLOR_PAIR(9));
                    mvprintw(i + passingHeight, j + passingWidth, " ");
                    attroff(COLOR_PAIR(9));
                }
            }
            // Draw letter position if this is normal mode
            else if(j%5 == 0 && j%10 != 0 &&  i%5 == 3 && idxNum[i][j] != 300)
            {
                attron(COLOR_PAIR((int)idxObj[i][j] % 8));
                mvprintw(i + passingHeight, j + passingWidth, "%c", idxObj[i][j]);
                attroff(COLOR_PAIR((int)idxObj[i][j] % 8));
            }
            // Draw current box
            else if(j >= x && j - x <= 9 && i >= y && i - y <= 4)
            {
                attron(COLOR_PAIR(8));
                mvprintw(i + passingHeight, j + passingWidth, " ");
                attroff(COLOR_PAIR(8));
            }
            // Draw selected box
            else if(j >= prevX && j - prevX <= 9 && i >= prevY && i - prevY <= 4)
            {
                attron(COLOR_PAIR(8));
                mvprintw(i + passingHeight, j + passingWidth, " ");
                attroff(COLOR_PAIR(8));
            }
            // Draw the horizontal border of the cell
            else if(i%5 == 0 && j%10 != 0)
            {
                // Using "Help" function, draw in red
                if(lineHelp[i][j] != 0)
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(i + passingHeight, j + passingWidth, "_");
                    attroff(COLOR_PAIR(1));
                    lineHelp[i][j]--;
                }
                // Otherwise, draw in blue
                else
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(i + passingHeight, j + passingWidth, "_");
                    attroff(COLOR_PAIR(4));
                }
            }
            // Draw the vertical line of the cell
            else if(j == 0 || j == width + 1 || j%10 == 0)
            {
                // Using "Help" function, draw in red
                if(lineHelp[i][j] != 0)
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(i + passingHeight, j + passingWidth, "|");
                    attroff(COLOR_PAIR(1));
                    lineHelp[i][j]--;
                }
                // Otherwise, draw in blue
                else
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(i + passingHeight, j + passingWidth, "|");
                    attroff(COLOR_PAIR(4));
                }
            }
        }
    }
    // Update screen
    refresh();
}
