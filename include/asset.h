#ifndef ASSET_H
#define ASSET_H

#include "raylib.h"

struct AssetManager { //To load the data
    AssetManager();
    ~AssetManager();

    Texture2D menu ,
              info ,
              game ,
               map ;
    Font title ,
      listFont ,
     inputFont ,
       askFont ;
    
};

#endif