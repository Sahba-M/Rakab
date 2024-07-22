#include <raylib.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include"menu.h"


MenuGame::MenuGame()
{
    screenWidth = 1075;
    screenHeight = 636;
    currentScreen = MENU;
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
    textColor  = {4, 9, 72, 255};

    Font font = LoadFont ("C:/font/title.otf");
    const char* text = "Rakab";
    Vector2 textPosition = { 100, 100 };
    
    DrawTextEx(font, text, (Vector2){ 430, 50 }, 90, 2, textColor);
}

void  MenuGame::setList()
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

bool MenuGame::exit ()
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
 void MenuGame::help()
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
 void MenuGame::start()
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

 void MenuGame::setImage()
 {
    Image image = LoadImage("C:/assets/background.png"); 
    Texture2D backgroundImage = LoadTextureFromImage(image);
    
    DrawTexture(backgroundImage, 0, 0, WHITE);
 }

void MenuGame::setCheckMenu(bool checkMenu)
{
   this->checkMenu = checkMenu;
}
bool MenuGame::getCheckMenu()
{
    return checkMenu;
}
int MenuGame::getScreen()
{
    return currentScreen;
}







// enum GameScreen { MENU = 0, IMAGE }; 
 
// int main() { 
//     // Initialization 
//     const int screenWidth = 800; 
//     const int screenHeight = 450; 
//     InitWindow(screenWidth, screenHeight, "raylib - switch screen example"); 
 
//     // Load image 
//     Texture2D image = LoadTexture("image.png"); // Ensure "image.png" is in the same directory as the executable 
 
//     GameScreen currentScreen = MENU; 
//     Rectangle button = {screenWidth / 2.0f - 50, screenHeight / 2.0f - 25, 100, 50}; 
 
//     SetTargetFPS(60);               // Set our game to run at 60 frames-per-second 
 
//     // Main game loop 
//     while (!WindowShouldClose())    // Detect window close button or ESC key 
//     { 
//         // Update 
//         if (currentScreen == MENU) { 
//             if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { 
//                 currentScreen = IMAGE; 
//             } 
//         } 
 
//         // Draw 
//         BeginDrawing(); 
 
//         ClearBackground(RAYWHITE); 
 
//         if (currentScreen == MENU) { 
//             DrawRectangleRec(button, GRAY); 
//             DrawText("Click me", screenWidth / 2 - 40, screenHeight / 2 - 10, 20, DARKGRAY); 
//         } else if (currentScreen == IMAGE) { 
//             DrawTexture(image, screenWidth / 2 - image.width / 2, screenHeight / 2 - image.height / 2, WHITE); 
//         } 
 
//         EndDrawing(); 
//     } 
 
//     // De-Initialization 
//     UnloadTexture(image);   // Unload image texture 
//     CloseWindow();          // Close window and OpenGL context 
 
//     return 0; 
// }