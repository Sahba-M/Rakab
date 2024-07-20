#include <raylib.h>

#include"menu.h"

MenuGame::MenuGame()
{
    screenWidth = 1075;
    screenHeight = 636;
}
int MenuGame::getScreenWidth()
{
    return screenWidth;
}
int MenuGame::getScreenHeight()
{
    return screenHeight;
}
MenuGame::~MenuGame()
{
    // UnloadTexture(backgroundImage);
}

void  MenuGame::setBackGround()
{
    SetTargetFPS(60); // Set the target frames-per-second
    Image image = LoadImage("C:/assets/photoMenu.png"); 
    Texture2D backgroundImage = LoadTextureFromImage(image);
    
    DrawTexture(backgroundImage, 0, 0, WHITE);

    
   
  
}
void  MenuGame::setTitle()
{
    Color textColor;
    textColor  = {7, 14, 115, 250};

    Font font = LoadFont ("C:/font/titleFont.ttf");
    const char* text = "Rakab";

     //DrawText ( "Rakab" , 250 , 100 , 60 , textColor );
     Vector2 textPosition = { 100, 100 };
   
     DrawTextEx(font, text, (Vector2){ 750, 50 }, 100, 2, textColor);
}