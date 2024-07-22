#include <iostream>
#include <raylib.h>

#include "control.h"
#include "graphic.h"

int main()
{
    
    GraphicGame graphic;
    
    InitWindow(graphic.getScreenWidth(), graphic.getScreenHeight(), "Rakab Game");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (graphic.getScreen() == MENU)
        {
            graphic.setBackGround();
            graphic.setTitle();
            graphic.setList();
            if (graphic.exit())
            {
                return 0 ;
            }
        }
        else if (graphic.getScreen() == IMAGE)
        {
            graphic.setImage();
            graphic.getInformation();
        }
        

        EndDrawing();
    }
    
    Control rakab ;
    rakab.run();
    return 0;
}