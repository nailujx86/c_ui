#include "UI.h"

#if defined __unix__
void setColor(short f, short b) {
    printf("\033[%d;%dm", f, b);
}
void setCursorPos(int x, int y) {
    printf("\033[%d;%dH", x + 1, y + 1);
}
WINSIZE getWinSize() {
    struct winsize max;
    ioctl(0, TIOCGWINSZ, &max);
    WINSIZE size;
    size.height = max.ws_row;
    size.width = max.ws_col;
    return size;
}
int waitForArrowOrEnter() {
    int tmp;
    tmp = getchar();
    while (tmp != '\033' || tmp != 0x0D) {
        tmp = getchar();
    }
    if (tmp == 0x0D) {
        fflush(stdin);
        return KEY_ENTER;
    }
    if (tmp == '\033') {
        getchar();
        switch (getchar()) {
            case 'A':
                fflush(stdin);
                return KEY_UP;
            case 'B':
                fflush(stdin);
                return KEY_DOWN;
            case 'C':
                fflush(stdin);
                return KEY_RIGHT;
            case 'D':
                fflush(stdin);
                return KEY_LEFT;
            default:
                fflush(stdin);
                return waitForArrowOrEnter();
        }
    }
    fflush(stdin);
    return 0;
}
#elif defined _WIN32
void setColor(short f, short b) {
    short colorAtt = f + b * 16;
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
int waitForArrowOrEnter() {
    int tmp;
    tmp = getch();
    while (tmp != 0xE0 && tmp != 0x0D) {
        tmp = getch();
    }
    if (tmp == 0x0D) {
        fflush(stdin);
        return KEY_ENTER;
    }
    if (tmp == 0xE0) {
        tmp = getch();
        switch (tmp) {
            case 72:
                fflush(stdin);
                return KEY_UP;
            case 75:
                fflush(stdin);
                return KEY_LEFT;
            case 80:
                fflush(stdin);
                return KEY_DOWN;
            case 77:
                fflush(stdin);
                return KEY_RIGHT;
            default:
                fflush(stdin);
                return waitForArrowOrEnter();
        }
    }
    fflush(stdin);
    return 0;
}

#else
void setColor(short f, short b) {}
#endif

void printDialog(char* texts[], int len, int x, int y, int width, int fC, int bC, int lastInput, int firstMenu) {
    setCursorPos(x, y);
    setColor(fC, bC);
    if (firstMenu) {
        printf("╔═%s", texts[0]);
        for (int i = 0; i < width - strlen(texts[0]) - 1; i++) {
            printf("═");
        }
        printf("╗");
    } else {
        //printf("╔═════════════════════════════════════╗");
        printf("╔");
        for (int i = 0; i < width; i++) {
            printf("═");
        }
        printf("╗");
    }
    firstMenu = !firstMenu;
    for (int i = 1; i < len + firstMenu; i++) {
        setCursorPos(x, y + i);
        printf("║ %s", texts[i - firstMenu]);
        for (int j = 0; j < width - 1 - strlen(texts[i - firstMenu]); j++) {
            printf(" ");
        }
        printf("║");
        //printf("║ %-35s ║\n", texts[i - firstMenu]);
    }
    setCursorPos(x, y + len + firstMenu);
    printf("╚");
    for (int i = 0; i < width; i++) {
        printf("═");
    }
    printf("╝");
    //printf("╚═════════════════════════════════════╝");
    if (lastInput) {
        setCursorPos(x + strlen(texts[len - 1]) + 2, y + len - 1 + firstMenu);
    }
}

int launchMenu(char* texts[], int len, int x, int y, int width, int fC, int bC, int firstMenu, char selector, int textStartIndex) {
    char** tempArr = (char**)malloc(sizeof(char*) * len);
    for (int i = 0; i < len; i++) {
        char* temp = (char*)calloc(1, sizeof(char) * (strlen(texts[i]) + 3));
        if (i >= firstMenu + textStartIndex) {
            strcpy(temp, "  ");
            strcat(temp, texts[i]);
        } else {
            strcpy(temp, texts[i]);
        }
        tempArr[i] = temp;
    }
    printDialog(tempArr, len, x, y, width, fC, bC, 0, firstMenu);
    for (int i = 0; i < len; i++) {
        char* tmp = tempArr[i];
        free(tmp);
    }
    free(tempArr);
    int selection = 0;
    setCursorPos(x + 2, y + 1 + textStartIndex + selection);
    printf("%c", selector);
    setCursorPos(0, 0);
    while (1) {
        int option = waitForArrowOrEnter();
        int newSelection = selection;
        if (option == KEY_UP) {
            newSelection = selection - 1;
            if (newSelection < 0)
                newSelection = len - firstMenu - textStartIndex - 1;
        } else if (option == KEY_DOWN) {
            newSelection = selection + 1;
            if (newSelection > len - firstMenu - textStartIndex - 1)
                newSelection = 0;
        } else if (option == KEY_ENTER) {
            return selection;
        }
        setCursorPos(x + 2, y + 1 + textStartIndex + selection);
        printf(" ");
        setCursorPos(x + 2, y + 1 + textStartIndex + newSelection);
        printf("%c", selector);
        setCursorPos(0, 0);
        selection = newSelection;
    }
}

int launchDialog(char* texts[], int len, int x, int y, int width, int fC, int bC, int firstMenu, int selectionfC, int selectionbC, int dialogStartIndex) {
    int minWidth = 4;
    for (int i = dialogStartIndex + firstMenu; i < len; i++) {
        minWidth += strlen(texts[i]) + 1;
    }
    if (width < minWidth)
        width = minWidth;
    char** tempArr = (char**)malloc(sizeof(char*) * (dialogStartIndex + firstMenu + 1));
    for (int i = 0; i < (dialogStartIndex + firstMenu); i++) {
        tempArr[i] = texts[i];
    }
    char gap[] = "";
    tempArr[dialogStartIndex + firstMenu] = gap;
    printDialog(tempArr, dialogStartIndex + firstMenu + 1, x, y, width, fC, bC, 0, firstMenu);
    free(tempArr);
    int selection = 0;
    while (1) {
        setCursorPos(x + 2, y + 1 + dialogStartIndex - firstMenu + 1);
        for (int i = dialogStartIndex + firstMenu; i < len; i++) {
            if (i - dialogStartIndex - firstMenu == selection) {
                setColor(selectionfC, selectionbC);
                printf(" %s ", texts[i]);
            } else {
                setColor(fC, bC);
                printf(" %s ", texts[i]);
            }
        }
        setCursorPos(0, 0);
        int option = waitForArrowOrEnter();
        int newSelection = selection;
        if (option == KEY_LEFT) {
            newSelection = selection - 1;
            if (newSelection < 0)
                newSelection = len - firstMenu - dialogStartIndex - 1;
        } else if (option == KEY_RIGHT) {
            newSelection = selection + 1;
            if (newSelection > len - firstMenu - dialogStartIndex - 1)
                newSelection = 0;
        } else if (option == KEY_ENTER) {
            return selection;
        }
        selection = newSelection;
    }
}

int calculateMinWidth(char* texts[], int len) {
    int minWidth = 3;
    for(int i = 0; i < len; i++) {
        minWidth = minWidth < strlen(texts[i]) ? strlen(texts[i]) + 3 : minWidth;
    }
    return minWidth;
}