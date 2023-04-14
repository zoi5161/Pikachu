#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Support for random function

// If it's Windows, use the following 4 libraries:
#include <Windows.h> // Graphics Library for Windows
#include <curses.h> // Graphics Library for Windows
#include <time.h>
#include <mmsystem.h> // Audio support library

#pragma comment(lib, "winmm.lib") // Link the winmm.lib library into the program

// If it's Mac OS, use the 3 libraries below:
// #include <chrono> // Support for sleep function
// #include <thread> // Support for sleep function
// #include <ncurses.h> // Graphics library for Mac OS

#define ppxy prevX, prevY, x, y
#define ippxy int prevX, int prevY, int x, int y
#define iPPXY int &prevX, int &prevY, int &x, int &y

#define heightS 19
#define widthS 79
#define heightM 39
#define widthM 79
#define heightB 39
#define widthB 159

#define passingHeightMenu 12

using namespace std;