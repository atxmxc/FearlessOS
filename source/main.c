#include <nds.h>
#include <stdio.h>

PrintConsole topScreen;
PrintConsole bottomScreen;

int option = 0;

void drawTopBar()
{
    consoleSelect(&topScreen);
    consoleClear();

    iprintf("\x1b[2;0H################################");
    iprintf("\x1b[3;0H#                              #");
    iprintf("\x1b[4;0H#      FEARLESS  LAUNCHER      #");
    iprintf("\x1b[5;0H#                              #");
    iprintf("\x1b[6;0H################################");
}

void drawBottomMenu()
{
    consoleSelect(&bottomScreen);
    consoleClear();

    iprintf("\n\n           FEARLESS OS\n");
    iprintf("       LEFT/RIGHT to select\n");
    iprintf("           A to launch\n\n");

    if (option == 0)
        iprintf("   [ R4 MENU ]    FEARLESS");
    else
        iprintf("     R4 MENU    [ FEARLESS ]");
}

int main(void)
{
    powerOn(POWER_ALL);

    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);

    consoleInit(&topScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    consoleInit(&bottomScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 30, 0, false, true);

    drawTopBar();
    drawBottomMenu();

    while (1)
    {
        scanKeys();
        int keys = keysDown();

        if (keys & KEY_LEFT)  { option = 0; drawBottomMenu(); }
        if (keys & KEY_RIGHT) { option = 1; drawBottomMenu(); }

        if (keys & KEY_A)
        {
            consoleSelect(&bottomScreen);
            consoleClear();
            iprintf("\n\n   Launching...");
        }

        swiWaitForVBlank();
    }
}
