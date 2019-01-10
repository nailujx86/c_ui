#include "stdlib.h"

#ifndef UI_HEADER
#define UI_HEADER

#if defined __unix__
#include <stdio.h>
#include <sys/ioctl.h>
#define clrscr() system("clear")
#define utf8() {}

#define C_B_BLACK 40
#define C_B_RED 41
#define C_B_GREEN 42
#define C_B_YELLOW 43
#define C_B_BLUE 44
#define C_B_MAGENTA 45
#define C_B_CYAN 46
#define C_B_WHITE 47

#define C_B_BBLACK 100
#define C_B_BRED 101
#define C_B_BGREEN 102
#define C_B_BYELLOW 103
#define C_B_BBLUE 104
#define C_B_BMAGENTA 105
#define C_B_BCYAN 106
#define C_B_BWHITE 107

#define C_F_BLACK 30
#define C_F_RED 31
#define C_F_GREEN 32
#define C_F_YELLOW 33
#define C_F_BLUE 34
#define C_F_MAGENTA 35
#define C_F_CYAN 36
#define C_F_WHITE 37

#define C_F_BBLACK 90
#define C_F_BRED 91
#define C_F_BGREEN 92
#define C_F_BYELLOW 93
#define C_F_BBLUE 94
#define C_F_BMAGENTA 95
#define C_F_BCYAN 96
#define C_F_BWHITE 97

#elif defined _WIN32
#include <windows.h>
#define clrscr() system("cls")
#define utf8() SetConsoleOutputCP(CP_UTF8)

#define C_B_BLACK 0
#define C_B_RED 4
#define C_B_GREEN 2
#define C_B_YELLOW 6
#define C_B_BLUE 1
#define C_B_MAGENTA 5
#define C_B_CYAN 3
#define C_B_WHITE 7

#define C_B_BBLACK 8
#define C_B_BRED 12
#define C_B_BGREEN 10
#define C_B_BYELLOW 14
#define C_B_BBLUE 9
#define C_B_BMAGENTA 13
#define C_B_BCYAN 11
#define C_B_BWHITE 15

#define C_F_BLACK 0
#define C_F_RED 4
#define C_F_GREEN 2
#define C_F_YELLOW 6
#define C_F_BLUE 1
#define C_F_MAGENTA 5
#define C_F_CYAN 3
#define C_F_WHITE 7

#define C_F_BBLACK 8
#define C_F_BRED 12
#define C_F_BGREEN 10
#define C_F_BYELLOW 14
#define C_F_BBLUE 9
#define C_F_BMAGENTA 13
#define C_F_BCYAN 11
#define C_F_BWHITE 15

#else

#define utf8() {}
#define C_B_BLACK 0
#define C_B_RED 4
#define C_B_GREEN 2
#define C_B_YELLOW 6
#define C_B_BLUE 1
#define C_B_MAGENTA 5
#define C_B_CYAN 3
#define C_B_WHITE 7

#define C_B_BBLACK 8
#define C_B_BRED 12
#define C_B_BGREEN 10
#define C_B_BYELLOW 14
#define C_B_BBLUE 9
#define C_B_BMAGENTA 13
#define C_B_BCYAN 11
#define C_B_BWHITE 15

#define C_F_BLACK 0
#define C_F_RED 4
#define C_F_GREEN 2
#define C_F_YELLOW 6
#define C_F_BLUE 1
#define C_F_MAGENTA 5
#define C_F_CYAN 3
#define C_F_WHITE 7

#define C_F_BBLACK 8
#define C_F_BRED 12
#define C_F_BGREEN 10
#define C_F_BYELLOW 14
#define C_F_BBLUE 9
#define C_F_BMAGENTA 13
#define C_F_BCYAN 11
#define C_F_BWHITE 15

#endif

void setColor(short f, short b);
void setCursorPos(int x, int y);

typedef struct {
    int width, height;
} WINSIZE;

WINSIZE getWinSize();
void printDialog(char* texts[], int x, int y, int width, int leftOffset, int fC, int bC, int lastInput, int firstMenu);
#endif