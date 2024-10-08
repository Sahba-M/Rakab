#include<iostream>
#include "input.h"
#include "raylib.h"
#include <string.h>

InputBox::InputBox ( float posX , float posY , float width , float height ) 
{
    bounds = { posX , posY, width, height }; // set dimensions 
    text[0] = '\0'; // Initialize text as empty string
    active = false;
    editing = false;
}
char* InputBox::GetInput() 
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
        if (CheckCollisionPointRec(GetMousePosition(), bounds)) // Check if mouse is inside bounds
        {
            active = true;
            editing = true;
        }
        else
        {
            active = false;
            editing = false;
        }
    }
    if ( active && editing )  // Check keyboard input if active
    {
        int key = GetKeyPressed(); //The key pressed by the user

        if (key > 0 && strlen(text) < 255) 
        {
            if ((key >= 32) && (key <= 125) && key != 45) // Check if the key is within the printable ASCII range
            {
                int len = strlen ( text ); //text length
                text[len] = (char) key;
                text[len + 1] = '\0'; // Null-terminate the string
            }
            else if (key == KEY_BACKSPACE && strlen(text) > 0) // handle backspace
            {
                int len = strlen( text );
                text[len - 1] = '\0'; // remove last character
            }
        }
    }
}
void InputBox::DrawName() 
{
    float roundness = 0.4f; // for rounding rectangle corners
    Color color = { 171 , 220 , 245 , 225 }; // Background color
    Color borderColor = { 6 , 87 , 128 , 255 }; // Border color
    
    DrawRectangleRounded(bounds, roundness, 0, color);

    
    if (text[0]== '\0') // Draw text or hint
    {
        DrawTextEx(myAsset.inputFont, "Name...", {bounds.x + 15, bounds.y + 25}, 25, 2,{124,135,145,255});
    }
    else
    {
        DrawTextEx(myAsset.inputFont, text, {bounds.x + 15, bounds.y + 25}, 25, 2, BLACK);
    }

    // Draw rectangle border if active
    if (active) // Is it clicked or not?
    {
        Rectangle border = {bounds.x, bounds.y, bounds.width, bounds.height};
        DrawRectangleRoundedLines(border, roundness, 0, 4, borderColor); // Only the margin
    }
}
void InputBox::DrawAge() 
{
    float roundness = 0.4f; // for rounding rectangle corners
    Color color = { 171 , 220 , 245 , 225 }; // Background color
    Color borderColor = { 6 , 87 , 128 , 255 }; // Border color

    DrawRectangleRounded(bounds, roundness, 0, color);

    // Draw text or hint
    if (text[0]== '\0')
    {
        DrawTextEx(myAsset.inputFont, "Age...", {bounds.x + 15, bounds.y + 25}, 25, 2,{124,135,145,255});
    }
    else
    {
        DrawTextEx(myAsset.inputFont, text, {bounds.x + 15, bounds.y + 25}, 25, 2, BLACK);
    }

    // Draw rectangle border if active
    if (active) // Is it clicked or not?
    {
        Rectangle border = {bounds.x, bounds.y, bounds.width, bounds.height};
        DrawRectangleRoundedLines(border, roundness, 0, 4, borderColor); // Only the margin
    }
}
bool InputBox::isEmpty() 
{
    return text[0] == '\0'; 
}
