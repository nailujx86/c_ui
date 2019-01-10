#include "UI.h"

#if defined __unix__
void setColor(short f, short b) {
    printf("\033[%d;%dm", f, b);
}
void setCursorPos(int x, int y) {
    printf("\033[%d;%dH", x+1, y+1);
}
WINSIZE getWinSize() {
    struct winsize max;
    ioctl(0, TIOCGWINSZ , &max);
    WINSIZE size;
    size.height = max.ws_row;
    size.width = max.ws_col;
    return size;
}
#elif defined _WIN32
void setColor(short f, short b) {
    short colorAtt = f + b*16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorAtt);
}
void setCursorPos(int x, int y) {
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}
WINSIZE getWinSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    WINSIZE size;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    size.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    size.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return size;
}

#else
void setColor(short f, short b) {}
#endif

void printDialog(char* texts[], int len, int x, int y, int width, int fC, int bC, int lastInput, int firstMenu) {
    setCursorPos(x, y);
    setColor(fC, bC);
    if (firstMenu) {
        printf("╔═%s", texts[0]);
        for (int i = 0; i < 36 - strlen(texts[0]); i++) {
            printf("═");
        }
        printf("╗");
    } else {
        printf("╔═════════════════════════════════════╗");
    }
    firstMenu = !firstMenu;
    for (int i = 1; i < len + firstMenu; i++) {
        setCursorPos(x, y + i);
        printf("║ %-35s ║\n", texts[i - firstMenu]);
    }
    setCursorPos(x, y + len + firstMenu);
    printf("╚═════════════════════════════════════╝");
    if (lastInput) {
        setCursorPos(x + strlen(texts[len - 1]) + 2, y + len - 1 + firstMenu);
    }
}
