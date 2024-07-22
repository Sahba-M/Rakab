#include <raylib.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include"graphic.h"


GraphicGame::GraphicGame()
{
    screenWidth = 1075;
    screenHeight = 636;
    currentScreen = MENU;
}
int GraphicGame::getScreenWidth()
{
    return screenWidth;
}
int GraphicGame::getScreenHeight()
{
    return screenHeight;
}
GraphicGame::~GraphicGame()
{
    // UnloadTexture(backgroundImage);
}

void  GraphicGame::setBackGround()
{
    
    SetTargetFPS(60); // Set the target frames-per-second
    Image image = LoadImage("C:/assets/photoMenu.png"); 
    Texture2D backgroundImage = LoadTextureFromImage(image);
    
    DrawTexture(backgroundImage, 0, 0, WHITE);
}

void  GraphicGame::setTitle()
{
    Color textColor;
    textColor  = {4, 9, 72, 255};

    Font font = LoadFont ("C:/font/title.otf");
    const char* text = "Rakab";
    Vector2 textPosition = { 100, 100 };
    
    DrawTextEx(font, text, (Vector2){ 430, 50 }, 90, 2, textColor);
}

void  GraphicGame::setList()
{
    buttons.reserve(4);
    Font font = LoadFont ("C:/font/listFont.otf");

    // bool colorChanged = false;
    float timer = 0.0f;
    const float changeDuration = 2.0f; // Duration in seconds to revert colors


   buttons[0].text = "New Game";
   buttons[0].bounds = { 450, 230, 250, 45 };
   
   buttons[1].text = "Load Game";
   buttons[1].bounds = { 450, 280, 250, 45 };

   buttons[2].text = "Help";
   buttons[2].bounds = { 450, 330, 250, 45 };

   buttons[3].text = "Exit";
   buttons[3].bounds = { 450, 380, 250, 45 };

    Vector2 mousePosition = GetMousePosition();

    for (int i = 0 ; i < 4 ; i++)
    {
        if (CheckCollisionPointRec(mousePosition, buttons[i].bounds)) 
        {
            // Change colors on button click
            buttons[i].buttonColor = { 0 , 0 , 0 , 110 };
            buttons[i].color = { 234 , 237 , 240 , 255 };
        }
        else 
        {
            buttons[i].color = BLACK;
            buttons[i].buttonColor = {0 , 0 , 0 , 30};
        }
    }

    // Draw button background
    // Draw button text
    DrawRectangle (buttons[0].bounds.x, buttons[0].bounds.y, buttons[0].bounds.width, buttons[0].bounds.height, buttons[0].buttonColor);
    DrawTextEx(font , buttons[0].text, { buttons[0].bounds.x + 70 , buttons[0].bounds.y + 10} , 30 , 2, buttons[0].color);
    DrawRectangle (buttons[1].bounds.x, buttons[1].bounds.y, buttons[1].bounds.width, buttons[1].bounds.height, buttons[1].buttonColor);
    DrawTextEx(font , buttons[1].text, { buttons[1].bounds.x + 67 , buttons[1].bounds.y + 10} , 30 , 2, buttons[1].color);
    DrawRectangle (buttons[2].bounds.x, buttons[2].bounds.y, buttons[2].bounds.width, buttons[2].bounds.height, buttons[2].buttonColor);
    DrawTextEx(font , buttons[2].text, { buttons[2].bounds.width/2 + buttons[2].bounds.x - 25 , buttons[2].bounds.y + 10} , 30 , 2, buttons[2].color);
    DrawRectangle (buttons[3].bounds.x, buttons[3].bounds.y, buttons[3].bounds.width, buttons[3].bounds.height, buttons[3].buttonColor);
    DrawTextEx(font , buttons[3].text, { buttons[3].bounds.width/2 + buttons[3].bounds.x - 25 , buttons[3].bounds.y + 10} , 30 , 2, buttons[3].color);

    start();
    help();
}   

bool GraphicGame::exit ()
{
    Vector2 mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition, buttons[3].bounds)) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            CloseWindow(); // Close the window and exit the program
            return true;
        }
    }
    return false;
}
 void GraphicGame::help()
 {
    Vector2 mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition, buttons[2].bounds))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            system ("start C:/assets/help.pdf");
        }
        
    } 
 }
 void GraphicGame::start()
 {
    Vector2 mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition, buttons[0].bounds))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentScreen = IMAGE;
        }
        
    } 
 }

 void GraphicGame::setImage()
 {
    Image image = LoadImage("C:/assets/background.png"); 
    Texture2D backgroundImage = LoadTextureFromImage(image);
    
    DrawTexture(backgroundImage, 0, 0, WHITE);
 }

void GraphicGame::setCheckMenu(bool checkMenu)
{
   this->checkMenu = checkMenu;
}
bool GraphicGame::getCheckMenu()
{
    return checkMenu;
}
int GraphicGame::getScreen()
{
    return currentScreen;
}

void GraphicGame::setRecInput()
{
    Rectangle inputBox = { 500, 200, 400, 60 };
    Color boxColor = LIGHTGRAY;
    char text[256] = "";  // Buffer for user input
    int textLength = 0;
    bool editing = false;

    

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, inputBox)) 
            {
                editing = true;  // Start editing
            } else {
                editing = false; // Stop editing
            }
        }
    }
    if (editing) 
    {
        boxColor = YELLOW;
        if (IsKeyPressed(KEY_BACKSPACE)) 
        {
            if (textLength > 0) 
            {
                textLength--;
                text[textLength] = '\0';  // Null-terminate the string
            }
        } else 
        {
            for (int key = KEY_SPACE; key <= KEY_Z; key++) 
            {
                if (IsKeyPressed(key) && textLength < 255) 
                {
                    text[textLength] = (char)key; // Add the character
                    textLength++;
                    text[textLength] = '\0'; // Null-terminate the string
                }
            }
        }
    }

    DrawRectangleRec(inputBox, boxColor);
    DrawText(text, inputBox.x + 10, inputBox.y + 20, 20, BLACK);

}