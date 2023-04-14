// Run these 2 commands to execute the program on Mac OS
/* 
    g++ Game.cpp -o Game -lncurses
    ./Game
*/

// Run these 2 commands to execute the program on Windows
/* 
    g++ Game.cpp -o Game -lpdcurses
    ./Game
*/

#include "Header.h"
#include "Menu.h"
#include "Sign.h"
#include "Tutorial.h"
#include "GameMode.h"
#include "Map.h"
#include "Pause.h"
#include "Warn.h"
#include "Finish.h"
#include "Setup.h"
#include "Input.h"
#include "Draw.h"
#include "Logic.h"
#include "Sound.h"

// Menu
bool endMenu = false, played = false, newGame = true, signUp = false;
int dirMenu = 0, chooseMenu = 1, prevMode = 0, chooseWarnNewGame = 1;

// Sound
bool soundMN = true, soundDele = false, soundErr = false, soundFi = false;

char box1[9] = "SIGN UP ";
char box2[9] = "SIGN IN ";
char box3[9] = "TUTORIAL";
char box4[5] = "EXIT";

char box5[9] = "NEW GAME";
char box6[9] = "CONTINUE";

// Sign in // Sign up
bool endSign = true, endUser = false, endPass = true, endSeen = true, endReturnSign = false, warnAcc = false;
char user[20], pass[20];

// Tutorial
bool endTutorial = true;

// Game mode
bool endGM = true, modeHard = true;
int dirGM = 0, chooseGM = 2;

char boxGM1[7] = "Normal";
char boxGM2[8] = "Endless";

// Map
bool endMap = true;
int dirMap = 0, chooseMap = 2, Map = 0;

// Pause
bool endPause = true;
int dirPause = 0, choosePause = 1;

// Warn
bool endWarn = true;
int dirWarn = 0, chooseWarn = 1;

// Finish
bool endFinish = true, win = false;

// Game
bool endGame = true, confirm = false;
int height = heightS, width = widthS;
int dir, x, y, randomObj, score = 100, prevX, prevY, last = 0, hz = 0, totalTime = 100, round = 1;
int passingHeight, passingWidth;
int hour, minute, second, millisec;

int obj[27], idxNum[heightB+2][widthB+2], greenBlock[heightB+2][widthB+2], redBlock[heightB+2][widthB+2];
int line[heightB+2][widthB+2], lineOut[heightB+3][widthB+3], lineEnd[heightB+2][widthB+2], lineHelp[heightB+2][widthB+2];
int resetNum[heightB+2][widthB+2], resetLine[heightB+2][widthB+2], resetLineOut[heightB+3][widthB+3], resetLineEnd[heightB+2][widthB+2];

char idxObj[heightB+2][widthB+2];
string backgroundMenu1[41], backgroundMenu2[39], backgroundGame[heightB+2];
string backgroundGM[4], backgroundGMEasy[9], backgroundGMHard[9], backgroundGMReturn[5];
string backgroundMap[4], backgroundMapS[8], backgroundMapM[10], backgroundMapB[12];
string backgroundPause[4], backgroundWarn[10], backgroundNext[5];
string backgroundSignIn[37], backgroundSignUp[37];
string backgroundTutorial[42];
string backgroundWinner[35], backgroundLoser[35];

// Some text boxes
char boxConfirm[37] = "PRESS SPACE TO CONTINUE OR Q TO QUIT";
char boxResume[7] = "RESUME";

// Explain some variables and some conventions
/*
- round: used for normal mode
- Map: used for endless mode
- dir, dirGM, dirMenu,... : selection direction (up, down, left, right). Value conventions will be expressed in the relevant input functions
- hz:
	+ hz == 1: the menu displays backgroundMenu1
	+ hz == 2: the menu displays backgroundMenu2
- line[][]: using for drawing a cell border, drawing a line between 2 cells satisfying.
	+ line[][] == 0: draw blanks
	+ line[][] != 0 : draw line
- idxNum[][]: know that the box still exists or not. At the same time this variable also stores the value of type int for the letter position
	+ idxNum[][] == 300: box has been deleted
	+ idxNum[][] != 300: box still exists
	+ idxNum[][] == 500: rubbish value for this box
- prevX, prevY: x, y coordinates of previously selected cell. 200 is the rubbish value for these variables, meaning no boxes have been selected yet
*/

// Main
int main()
{
	initscr(); // Initialize the desktop environment: hide the mouse pointer, disable the display of line markers, and provide features such as storing the screen's cursor position so that the cursor can be moved to any position any on the screen.
	clear(); // Clear screen
	noecho(); // Turn off the display of characters entered from the keyboard
	cbreak(); // Do not wait for Enter, but execute the character you just entered
	curs_set(0); // Hide blinking cursor
    start_color(); // Enable color mode for the console.
    setupColor();
	srand(time(0));

	// Background Menu
	inputBackgroundMenu1(backgroundMenu1);
	inputBackgroundMenu2(backgroundMenu2);

	// Background Sign
	inputBackgroundSign(backgroundSignUp, "BackgroundSignUp.txt");
	inputBackgroundSign(backgroundSignIn, "BackgroundSignIn.txt");

	// Background Tutorial
	inputBackgroundTutorial(backgroundTutorial);

	// Background Game Mode
	inputBackgroundGM(backgroundGM);
	inputBackgroundGMEasy(backgroundGMEasy);
	inputBackgroundGMHard(backgroundGMHard);
    inputBackgroundGMReturn(backgroundGMReturn);

	// Background Map
	inputTextMap(backgroundMap);
	inputMapS(backgroundMapS);
	inputMapM(backgroundMapM);
	inputMapB(backgroundMapB);

	// Background Pause
	inputBackgroundPause(backgroundPause);

	// Background Warn
	inputBackgroundWarn(backgroundWarn);
	inputBackgroundNext(backgroundNext);

	// Background Finish
	inputBackgroundWinner(backgroundWinner);
	inputBackgroundLoser(backgroundLoser);

	while(!endMenu)
	{
		// Menu
		inputMenu(hz, dirMenu);
		// If you haven't played, draw the first 2 boxes are "SIGN UP" and "SIGN IN"
		if(!played)
			drawMenu(hz, chooseMenu, box1, box2, box3, box4, backgroundMenu1, backgroundMenu2);
		// If played, draw the first 2 boxes are "NEW GAME" and "CONTINUE"
		else
			drawMenu(hz, chooseMenu, box5, box6, box3, box4, backgroundMenu1, backgroundMenu2);
		logicMenu(chooseMenu, dirMenu, endMenu, endGM, played, endWarn, newGame, endSign, endTutorial, signUp);

		// Sign up // Sign in
		if(!played)
			while(!endSign)
			{
				// If your choose is Sign In
				if(chooseMenu == 2)
				{
					drawSign(backgroundSignIn, user, pass, endSeen, warnAcc, signUp);
					inputSign(user, pass, endUser, endPass, endSign, endSeen, endGM, warnAcc, signUp, chooseMenu);
				}
				// If your choose is Sign Up
				else
				{
					drawSign(backgroundSignUp, user, pass, endSeen, warnAcc, signUp);
					inputSign(user, pass, endUser, endPass, endSign, endSeen, endGM, warnAcc, signUp, chooseMenu);
				}
			}
		
		// Tutorial
		while(!endTutorial)
		{
			inputTutorial(endTutorial);
			drawTutorial(backgroundTutorial);
		}
		
		// Warn for clicking "New Game"
		while(!newGame)
		{
			inputWarn(dirWarn);
			drawWarn(chooseWarnNewGame, backgroundWarn, backgroundNext, backgroundGMReturn);
			logicWarnNewGame(dirWarn, chooseWarnNewGame, newGame, prevMode, last, round, endGM);
		}
		
		// Open the game mode selection interface
		while(!endGM)
		{
			played = true;
			// Is the game on yet ?
			if(!endGame)
			{
				endMap = true;
				// If the game run out of cells, reset the properties
				if(last == 0)
				{
					reset(idxObj, idxNum, line, lineOut, lineEnd, lineHelp, resetNum, resetLine, resetLineOut, resetLineEnd);

					if(modeHard == false)
					{
						if(round == 1)
						{
							height = heightS;
							width = widthS;
							passingHeight = 12;
							passingWidth = 65;
							backgroundSmall(backgroundGame);
						}
						else if(round == 2)
						{
							height = heightM;
							width = widthM;
							passingHeight = 3;
							passingWidth = 65;
							backgroundMedium(backgroundGame);
						}
						else if(round == 3)
						{
							height = heightB;
							width = widthB;
							passingHeight = 3;
							passingWidth = 30;
							backgroundBig(backgroundGame);
						}
					}
					else
					{
						if(Map == 1)
						{
							height = heightS;
							width = widthS;
							passingHeight = 12;
							passingWidth = 65;
							backgroundSmall(backgroundGame);
						}
						else if(Map == 2)
						{
							height = heightM;
							width = widthM;
							passingHeight = 3;
							passingWidth = 65;
							backgroundMedium(backgroundGame);
						}
						else if(Map == 3)
						{
							height = heightB;
							width = widthB;
							passingHeight = 3;
							passingWidth = 30;
							backgroundBig(backgroundGame);
						}
					}

					setupGame(height, width, x, y, prevX, prevY, score, choosePause, confirm, modeHard, round, Map, last, dir, hour, minute, second, millisec, totalTime, obj, randomObj, idxObj, idxNum, line, lineOut, lineEnd, greenBlock, redBlock);
				}
				
				// Open the game board
				while(!endGame)
				{
					// Losing if the time runs out
					if(minute == 0 && second == 0 && last != 0)
					{
						last = 0;
						endGame = true;
						round = 3;
						win = false;
						endFinish = false;
						prevMode = 0;
						// Confirming finish game
						while(!endFinish)
						{
							inputFinish(endFinish);
							drawFinish(backgroundWinner, backgroundLoser, totalTime, score, win, minute, second);
						}
						break;
					}
					// Game operation
					draw(height, width, passingHeight, passingWidth, x, y, prevX, prevY, hour, minute, second, score, last, round, modeHard, boxConfirm, backgroundGame, idxObj, idxNum, line, lineOut, lineEnd, lineHelp, resetNum, resetLine, resetLineOut, resetLineEnd, greenBlock, redBlock);
					input(dir);
					logic(ppxy, height, width, dir, last, score, endPause, endGame, endMap, confirm, obj, randomObj, idxObj, idxNum, line, lineOut, lineEnd, lineHelp, resetNum, resetLine, resetLineOut, resetLineEnd, greenBlock, redBlock, soundDele, soundErr, soundFi);
					// Sound
					if (soundDele == true) {
						soundDelete(soundDele);
					}else if (soundErr == true) {
						soundError(soundErr);
					}else if (soundFi == true) {
						soundFinish(soundFi);
					}
					// Game stop confirmation
					if(!endPause)
					{
						while(!endPause)
						{
							inputPause(dirPause);
							drawPause(choosePause, backgroundPause, box4, boxResume);
							logicPause(dirPause, choosePause, endPause, endGame);
						}
					}
					// If the box runs out, then time stands still
					else if(last != 0)
						runTime(hour, minute, second, millisec, endGame);
				}

				// If it is the last stage of normal mode, when the game runs out of slots, confirm victory
				if(round == 3 && last == 0)
				{
					win = true;
					prevMode = 0;
					endFinish = false;
					while(!endFinish)
					{
						inputFinish(endFinish);
						drawFinish(backgroundWinner, backgroundLoser, totalTime, score, win, minute, second);
					}
				}

				if(choosePause != 2)
				{
					if(!modeHard)
					{
						if(round == 3)
							round = 1;
						else if(confirm == true)
						{
							round++;
							endGame = false;
						}
						else if(confirm == false)
							round++;
					}
					else if(confirm == true)
						endGame = false;
				}
				else if(last == 0 && !modeHard)
					round++;
			}

			// If you are still in the game, skip the interfaces below
			if(!endGame)
				continue;

			// Open the game mode selection interface
			inputGameMode(dirGM);
			drawGM(chooseGM, backgroundGM, backgroundGMEasy, backgroundGMHard, backgroundGMReturn, boxGM1, boxGM2);
			logicGM(dirGM, chooseGM, endGM, endGame, modeHard, endMap, prevMode, last);

			// if the game run out of box in hard mode or switch from normal mode to hard mode, the map selection interface will be displayed.
			if(last == 0 || (last != 0 && !modeHard))
				while(!endMap)
				{
					inputMap(dirMap);
					drawMap(chooseMap, backgroundMap, backgroundMapS, backgroundMapM, backgroundMapB, backgroundGMReturn);
					logicMap(dirMap, chooseMap, endMap, endGame, modeHard, Map, prevMode);
				}

			// If you switch from normal mode to hard mode or vice versa, a warning interface is displayed.
			if((modeHard && prevMode == 1) || (!modeHard && prevMode == 2))
			{
				endWarn = false;
				while(!endWarn)
				{
					inputWarn(dirWarn);
					drawWarn(chooseWarn, backgroundWarn, backgroundNext, backgroundGMReturn);
					logicWarn(dirWarn, chooseWarn, endWarn, modeHard, prevMode, endGame, endMap, last, round);
				}
			}
		}
	}
	clear();
	getch();
	endwin(); // Return the console environment to its original state
	return 0;
}