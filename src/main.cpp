#include <iostream>
#include <raylib.h>

#include "control.h"
#include "menu.h"

int main()
{
    
    // MenuGame menu;
    
    // InitWindow(menu.getScreenWidth(), menu.getScreenHeight(), "Rakab Game");
    // SetTargetFPS(60);

    // while (!WindowShouldClose())
    // {
    //     BeginDrawing();

    //     if (menu.getCheckMenu())
    //     {
    //         menu.setBackGround();
    //         menu.setTitle();
    //         menu.setList();
    //         if (menu.exit())
    //         {
    //             return 0 ;
    //         }
    //     }
        

        

    //     EndDrawing();
    // }
    
    Control rakab ;
    rakab.run();
    return 0;
}