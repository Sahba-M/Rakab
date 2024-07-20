
#include"menu.h"

// MenuGame::MenuGame()
// {
//     screenWidth = 1075;
//     screenHeight = 636;
// }

MenuGame::~MenuGame()
{
    // UnloadTexture(backgroundImage);
}

void  MenuGame::setBackGround()
{
    // Initialize the window
    // InitWindow(screenWidth, screenHeight, "MainMenu");
    
    SetTargetFPS(60); // Set the target frames-per-second
    Image image = LoadImage("C:\\Users\\LENOVO\\Desktop\\iTop\\back.png"); 
    Texture2D backgroundImage = LoadTextureFromImage(image);
    
    DrawTexture(backgroundImage, 0, 0, WHITE);
}