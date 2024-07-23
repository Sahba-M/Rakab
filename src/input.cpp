#include "input.h"
#include "raylib.h"
#include <string.h>

InputBox::InputBox ( float posX , float posY , float width , float height ) 
{
    bounds = {posX , posY, width, height};
    text[0] = '\0'; // Initialize text as empty string
    active = false;
    editing = false;
}

const char* InputBox::GetInput() 
{
    return text;
}

void InputBox::setInputDefault ()
{
    text[0] = '\0';
}

void InputBox::Update() 
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
    {
        // Check if mouse is inside bounds
        if (CheckCollisionPointRec(GetMousePosition(), bounds)) 
        {
            active = true;
            editing = true;
        } else {
            active = false;
            editing = false;
        }
    }
    // Check keyboard input if active
    if ( active && editing ) 
    {
        int key = GetKeyPressed();

        if (key > 0 && strlen(text) < 255) 
        {
            // Check if the key is within the printable ASCII range
            if ((key >= 32) && (key <= 125)) 
            {
                // Append character to text
                int len = strlen(text);
                text[len] = (char)key;
                text[len + 1] = '\0'; // Null-terminate the string
            } else if (key == KEY_BACKSPACE && strlen(text) > 0) 
            {
                // Handle backspace
                int len = strlen(text);
                text[len - 1] = '\0'; // Remove last character
            }
        }
    }
}

void InputBox::Draw() 
{
    float roundness = 0.4f;
    Font font =  LoadFont ("C:/font/inputFont.otf");
    Color color = { 171 , 220 , 245 , 225 };
    Color borderColor = { 6 , 87 , 128 , 255 };
    DrawRectangleRounded(bounds , roundness , 0 , color);
    // Draw text
    DrawTextEx( font , text , {bounds.x + 15, bounds.y + 25} , 25 , 2 , BLACK);
    // Draw rectangle border if active
    if (active) 
    {
        Rectangle border = {bounds.x, bounds.y, bounds.width, bounds.height};
        DrawRectangleRoundedLines ( border , roundness , 0 , 4 , borderColor);
    }
}