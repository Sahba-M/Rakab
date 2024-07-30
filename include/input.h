#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"
#include "asset.h"

class InputBox {
    public:
        InputBox ( float posX , float posY , float width , float height );
        char* GetInput(); 
        void setInputDefault ();
        void Update(); //To update the status of an input box
        void DrawName(); //box drawing
        void DrawAge();
        bool isEmpty();


    private:
        Rectangle bounds;
        char text[256];
        bool active;
        bool editing;
        AssetManager myAsset; //an object from AssetManager
        

};

#endif