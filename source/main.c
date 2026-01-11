#include <nds.h>
#include <stdio.h>

PrintConsole top;
PrintConsole bottom;

int option = 0;

void drawMenu()
{
    consoleSelect(&bottom);
    consoleClear();

    iprintf("\n\n    FEARLESS OS\n");
    iprintf("  Use LEFT / RIGHT\n");
    iprintf("     Press A\n\n");

    if (option == 0)
        iprintf("    [ R4 MENU ]   CUSTOM MENU");
    else
        iprintf("      R4 MENU   [ CUSTOM MENU ]");
}

int main(int argc, char* argv[])
{
    powerOn(POWER_ALL);

    // TOP screen
    videoSetMode(MODE_0_2D);
    vramSetBankA(VRAM_A_MAIN_BG);

    consoleInit(&top, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

    // BOTTOM screen
    videoSetModeSub(MODE_0_2D);
    vramSetBankC(VRAM_C_SUB_BG);

    consoleInit(&bottom, 0, BgType_Text4bpp, BgSize_T_256x256, 30, 0, false, true);

    // Draw top screen
    consoleSelect(&top);
    consoleClear();
    iprintf("\n\n   FEARLESS OS");
    iprintf("\n   System Ready");

    // Draw bottom menu
    drawMenu();

    while (1)
    {
        scanKeys();
        int keys = keysDown();

        if (keys & KEY_LEFT) {
            option = 0;
            drawMenu();
        }

        if (keys & KEY_RIGHT) {
            option = 1;
            drawMenu();
        }

        if (keys & KEY_A) {
            consoleSelect(&bottom);
            consoleClear();
            iprintf("\n\n   Launching...");
        }

        swiWaitForVBlank();
    }

    return 0;
}
