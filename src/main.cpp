#include <iostream>
#include <raylib.h>

#include "control.h"
#include "asset.h"

int main()
{
    
    int screenWidth = 1075;
    int screenHeight = 636;
    InitWindow(screenWidth, screenHeight, "Rakab Game");
    Control rakab ;
    rakab.run();
    return 0;
    
    // while (!WindowShouldClose())
    // {

    //     if (graphic.getScreen() == INFO)
    //     {
    //         graphic.getInformation();
    //         rakab.getInformation();
    //     }

    //     BeginDrawing();

    //     if (graphic.getScreen() == MENU)
    //     {
    //         graphic.setBackGround();
    //         graphic.setTitle();
    //         graphic.setList();
    //         if (graphic.exit())
    //         {
    //             return 0 ;
    //         }
    //     }
    //     else if (graphic.getScreen() == NUMBER)
    //     {
    //         graphic.setImage();
    //         graphic.askNumber();
    //     }
    //     else if (graphic.getScreen() == INFO)
    //     {
    //         graphic.setImage();
    //         graphic.drawInput();
    //         // rakab.getInformation();
    //     }
    //     else if (graphic.getScreen() == GAME)
    //     {
    //         graphic.uploadGame();
    //     }

    //     EndDrawing();

    // }
    
}