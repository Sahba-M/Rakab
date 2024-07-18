#include <iostream>
#include <raylib.h>

#include "control.h"
// #include "player.h"
#include "menu.h"

int main()
{
    const int screenWidth = 1075;
    const int screenHeight = 636;
    MenuGame menu;
    
    InitWindow(screenWidth, screenHeight, "Rakab Game");

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        menu.setBackGround();

        EndDrawing();
    }
    
    Control rakab ;
    rakab.run();
    return 0;
}