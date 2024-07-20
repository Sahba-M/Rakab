#include <iostream>
#include <raylib.h>

#include "control.h"
#include "menu.h"

int main()
{
    
    MenuGame menu;
    
    InitWindow(menu.getScreenWidth(), menu.getScreenHeight(), "Rakab Game");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        menu.setBackGround();
        menu.setTitle();

        EndDrawing();
    }
    
    Control rakab ;
    rakab.run();
    return 0;
}