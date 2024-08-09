#include <iostream>
#include <raylib.h>

#include "control.h"
#include "asset.h"

int main()
{
    int screenWidth = 1075;
    int screenHeight = 636;
    InitWindow(screenWidth, screenHeight, "Rakab Game"); //opening window before loading pictures

    Control rakab ;
    rakab.startGame();
    return 0;
}