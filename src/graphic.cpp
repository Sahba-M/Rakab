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
    // UnloadImage(backgroundImage);
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
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
}


void GraphicGame::drawInput() 
{

            ClearBackground(RAYWHITE);


            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
                }
                else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }
}
int GraphicGame::getNumberofPlayer()
{
    return numberofPlayer;
}
void GraphicGame::setNumberofPlayer(int numberofPlayer)
{
    this->numberofPlayer = numberofPlayer;
}

void GraphicGame::askNumber()
{
    Font font = LoadFont ("C:/font/askFont.otf");
    Color recColor = {132 , 132 , 132 , 255};

    DrawTextEx( font , "Choose The Number Of Players :" , { 340 + 2 , 100 + 2 } , 35 , 2 , BLACK );
    DrawTextEx( font , "Choose The Number Of Players :" , { 340 - 2 , 100 - 2 } , 35 , 2 , BLACK );
    DrawTextEx( font , "Choose The Number Of Players :" , { 340 + 2 , 100 - 2 } , 35 , 2 , BLACK );
    DrawTextEx( font , "Choose The Number Of Players :" , { 340 - 2 , 100 + 2 } , 35 , 2 , BLACK );
    DrawTextEx( font , "Choose The Number Of Players :" , { 340 , 100 } , 35 , 2 , LIGHTGRAY );
    DrawRectangle ( 325 , 145 , 450 , 5 , recColor );

    numButtons.reserve(4);

    numButtons[0].text = "3";
    numButtons[0].bounds = { 430, 200, 100, 60 };
    
    numButtons[1].text = "4";
    numButtons[1].bounds = { 550, 200, 100, 60 };
 
    numButtons[2].text = "5";
    numButtons[2].bounds = { 430, 280, 100, 60 };
 
    numButtons[3].text = "6";
    numButtons[3].bounds = { 550, 280, 100, 60 };

    Vector2 mousePosition = GetMousePosition();

    for (int i = 0 ; i < 4 ; i++)
        {
            if (CheckCollisionPointRec(mousePosition, numButtons[i].bounds)) 
            {
                // Change colors on button click
                numButtons[i].buttonColor = { 154 , 107 , 198 , 200 };
                numButtons[i].color = { 234 , 237 , 240 , 255 };
            }
            else 
            {
                numButtons[i].buttonColor = { 197 , 169 , 218 , 200 };
                numButtons[i].color = BLACK;
            }
        }    

    for ( int i = 0 ; i < 4 ; i++ )
    {
        DrawRectangle (numButtons[i].bounds.x, numButtons[i].bounds.y, numButtons[i].bounds.width, numButtons[i].bounds.height, numButtons[i].buttonColor);
        DrawTextEx(font , numButtons[i].text, { numButtons[i].bounds.x + 40 , numButtons[i].bounds.y + 10 } , 30 , 2, numButtons[i].color);
    }

    for (int i = 0; i < 4; i++)
    {
      if (CheckCollisionPointRec(mousePosition, numButtons[i].bounds))
      {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            setNumberofPlayer(i + 3);
            break;
        }
      }
    }  
}
void GraphicGame::getInformationG()
{
    Font font =  LoadFont ("C:/font/askFont.otf");

    DrawTextEx( font , " Enter Your Name: " , { 340 + 2 , 100 + 2 } , 35 , 2 , BLACK );

    drawInput();
    setRecInput();

    // DrawTextEx( font , "Enter Your Age : " , { 340 - 2 , 100 - 2 } , 35 , 2 , BLACK );
    // DrawTextEx( font , "Enter Your Color: " , { 340 + 2 , 100 - 2 } , 35 , 2 , BLACK );
}
