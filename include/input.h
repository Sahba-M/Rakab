#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"
#include "asset.h"

class InputBox
{
    public:
        InputBox ( float posX , float posY , float width , float height ); // constructor to make inputBox
        char* GetInput(); // get data from players
        void setInputDefault (); // set inputBox to defult
        void Update(); //to update the status of an input box
        void DrawName(); // box drawing
        void DrawAge(); // box drawing
        bool isEmpty(); 

    private:
        Rectangle bounds;
        char text[256]; // for save name
        bool active; // for check clicking box
        bool editing; // for check editing box
        AssetManager myAsset; // an object from AssetManager
};
#endif