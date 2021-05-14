#include "UI.h"

int main(int argc, char const *argv[])
{
    utf8();
    char *menu[] = {"c_ui", "", "Dialog", "Dialog with Input", "Menu"};
    int option;
    option = launchMenu(menu, 5, 20, 8, 45, C_F_BWHITE, C_F_BBLACK, 1, '>', 1);
    switch (option)
    {
    case 0:
        clrscr();
        int dialogSelection;
        char *menuDialog[] = {"Dialog", "Which option?", "", "Option A", "Option B"};
        dialogSelection = launchDialog(menuDialog, 5, 20, 8, 30, C_F_BYELLOW, C_B_BBLUE, 1, C_F_MAGENTA, C_B_BWHITE, 2);
        return dialogSelection;

    case 1:
        clrscr();
        char *menuInput[] = {"Input Dialog", "", "Input: "};
        char inputChar[40];
        printDialog(menuInput, 3, 20, 8, 30, C_F_BLACK, C_B_WHITE, 1, 1);
        scanf("%s", inputChar);
        fflush(stdin);
        return 0;
    case 2:
        main(0, ((void *)0));
    }
}