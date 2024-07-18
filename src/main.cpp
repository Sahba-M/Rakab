#include <iostream>
#include <raylib.h>

#include "control.h"
#include "player.h"
#include "menu.h"

int main()
{
    MenuGame menu;
    while (!WindowShouldClose())
    {
        BeginDrawing();

        menu.setBackGround();

        EndDrawing();
    }
    
    Control rakab ;
    rakab.run();
    return 0;
}