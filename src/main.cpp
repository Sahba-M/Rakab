#include <iostream>
#include <raylib.h>

#include "control.h"

int main()
{
    

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