#ifndef ASSET_H
#define ASSET_H

#include "raylib.h"

struct AssetManager { // to load the datas

    AssetManager(); // to load pictures
    ~AssetManager(); // to unload pictures

    Texture2D menu ,
              info ,
              game ,
               map ,
             table ,
            winner ,
          soldier1 ,
          soldier2 ,
          soldier3 ,
          soldier4 ,
          soldier5 ,
          soldier6 ,
         soldier10 ,
              back ,
            winter ,
            spring ,
           princes ,
            virago ,
           drummer ,
            leader ,
         scarecrow ,
              dean ,
             horse ,
             end   ;
               
    Font title ,
      listFont ,
     inputFont ,
       askFont ,
       name ;
    
};

#endif