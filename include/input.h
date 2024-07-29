#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"
#include "asset.h"

class InputBox {
    public:
        InputBox ( float posX , float posY , float width , float height );
        const char* GetInput(); 
        void setInputDefault ();
        void Update();
        void Draw();


    private:
        Rectangle bounds;
        char text[256];
        bool active;
        bool editing;
        AssetManager myAsset;
        

};

#endif