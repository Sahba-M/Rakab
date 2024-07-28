#include <raylib.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include"graphic.h"


GraphicGame::GraphicGame()
{
    screenWidth = 1075;
    screenHeight = 636;
    screen = MENU;
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
            screen = NUMBER;
        }
    } 
 }

 void GraphicGame::setImage()
 {
    Font font = LoadFont ("C:/font/listFont.otf");
    Image image = LoadImage("C:/assets/background.png"); 
    Texture2D backgroundImage = LoadTextureFromImage(image);
    DrawTexture(backgroundImage, 0, 0, WHITE);

    TextButton goBack ;
    goBack.bounds = { 30 , 30 , 150 , 60 };
    goBack.text = "Back To MENU";
    Vector2 mousePosition = GetMousePosition();

    if (CheckCollisionPointRec(mousePosition, goBack.bounds))
    {
        goBack.color = { 234 , 237 , 240 , 255 };
        goBack.buttonColor = { 101 , 107 , 110 , 200};
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            screen = MENU;
        }
    } 
    else
    {
        goBack.color = BLACK;
        goBack.buttonColor = { 174 , 185 , 191 , 200};
    }

    DrawRectangleRounded (goBack.bounds , 0.4f , 0 , goBack.buttonColor);
    DrawTextEx(font , goBack.text, { goBack.bounds.x + 12 , goBack.bounds.y + 20 } , 25 , 2, goBack.color);

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
    return screen;
}
void GraphicGame::drawInput() 
{
    static int counter = 1 ;
    if (counter <= getNumberofPlayer())
    {
        Font font =  LoadFont ("C:/font/inputFont.otf");
        Color backColor = { 70 , 157 , 212 , 200 };
        char text[2] ; 
        text[0] = counter + '0';
        text[1] = '\0';

        Rectangle back = { 500 , 70 , 150 , 70 };
        DrawRectangleRounded ( back , 0.4f , 0 , {227, 214, 95, 200});
        DrawTextEx ( font , "Player" , { 525 , 90 } , 25 , 2 , BLACK );
        DrawTextEx ( font , text , { 615 , 90 } , 25 , 2 , BLACK );

        if ( next )
        {
            inputName.setInputDefault();
            inputAge.setInputDefault();
            next = false ;
        }

        back = { 320 , 160 , 270 , 75 };
        DrawRectangleRounded ( back , 0.4f , 0 , backColor );
        DrawTextEx( font , " Enter Your Name " , { 330 , 185 } , 30 , 2 , BLACK );
        inputName.Draw();
        back = { 320 , 245 , 270 , 75 };
        DrawRectangleRounded ( back , 0.4f , 0 , backColor );
        DrawTextEx( font , " Enter Your Age " , { 330 , 270 } , 30 , 2 , BLACK );
        inputAge.Draw();
    
        submit.bounds = { 500 , 350 , 150 , 70 };
        submit.text = "NEXT";

        Vector2 mousePosition = GetMousePosition();

        if (CheckCollisionPointRec(mousePosition, submit.bounds))
        {
            submit.color = { 234 , 237 , 240 , 255 };
            submit.buttonColor = { 22 , 122 , 11 , 200};
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                counter++;
                next = true;
            }
        } 
        else
        {
            submit.color = BLACK;
            submit.buttonColor = { 87 , 186 , 76 , 200};
        }
        DrawRectangleRounded (submit.bounds , 0.4f , 0 , submit.buttonColor);
        DrawTextEx(font , submit.text, { submit.bounds.x + 45 , submit.bounds.y + 20 } , 25 , 2, submit.color);
    }
    else screen = GAME; 



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
    float roundness = 0.3f;
    DrawTextEx( font , "Choose The Number Of Players :" , { 340 + 2 , 100 + 2 } , 35 , 2 , BLACK );
    DrawTextEx( font , "Choose The Number Of Players :" , { 340 - 2 , 100 - 2 } , 35 , 2 , BLACK );
    DrawTextEx( font , "Choose The Number Of Players :" , { 340 + 2 , 100 - 2 } , 35 , 2 , BLACK );
    DrawTextEx( font , "Choose The Number Of Players :" , { 340 - 2 , 100 + 2 } , 35 , 2 , BLACK );
    DrawTextEx( font , "Choose The Number Of Players :" , { 340 , 100 } , 35 , 2 , LIGHTGRAY );
    DrawRectangle ( 325 , 90 , 450 , 100 , recColor );

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
        DrawRectangleRounded (numButtons[i].bounds , roundness , 0 , numButtons[i].buttonColor);
        DrawTextEx(font , numButtons[i].text, { numButtons[i].bounds.x + 40 , numButtons[i].bounds.y + 10 } , 30 , 2, numButtons[i].color);
    }

    for (int i = 0; i < 4; i++)
    {
      if (CheckCollisionPointRec(mousePosition, numButtons[i].bounds))
      {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            setNumberofPlayer(i + 3);
            screen = INFO;
            break;
        }
      }
    }  
}
void GraphicGame::getInformation()
{
    inputName.Update();
    inputAge.Update();
}
void GraphicGame::transferInformation ( std::string & name , int & age )
{   
    if ( next )
    {
        name = inputName.GetInput();
        age = atoi(inputAge.GetInput());

        // std::cout << name << std::endl;
        // std::cout << age << std::endl;
        // std::cin >> name ;
        next = false ;
    }
}

void GraphicGame::uploadGame()
{
    Image image = LoadImage("C:/assets/backGame.png"); 
    Texture2D backgroundImage = LoadTextureFromImage(image);
    DrawTexture(backgroundImage, 0, 0, WHITE);

    Image mapimg = LoadImage("C:/assets/Map.png"); 
    Texture2D map = LoadTextureFromImage(mapimg);
    DrawTextureEx(map, (Vector2){200, 75}, 0.0f, 0.6f, WHITE);




}