
#include"menu.h"

MenuGame::MenuGame()
{
    screenWidth = 1075;
    screenHeight = 636;
}


void  MenuGame::setBackGround()
{
    
    // Initialize the window
    InitWindow(screenWidth, screenHeight, "MainMenu");
    
    // Load the background image
    Texture2D backgroundImage = LoadTexture("C:\\Users\\LENOVO\\Desktop\\iTop");
    
    SetTargetFPS(60); // Set the target frames-per-second
    
    DrawTexture(backgroundImage, 0, 0, WHITE);
     // Unload the background image
    UnloadTexture(backgroundImage);
    
    
}