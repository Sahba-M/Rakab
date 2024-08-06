#include "asset.h"

AssetManager::AssetManager()
{
    title = LoadFont ("C:/font/title.otf");
    listFont = LoadFont ("C:/font/listFont.otf");
    inputFont = LoadFont ("C:/font/inputFont.otf");
    askFont = LoadFont ("C:/font/askFont.otf");
    name = LoadFont ("C:/font/name1.otf");


    menu = LoadTexture("C:/assets/photoMenu.png");
    info = LoadTexture("C:/assets/background.png");
    game = LoadTexture("C:/assets/backGame.png");
    map = LoadTexture("C:/assets/Map.png");
    table = LoadTexture("C:/assets/table.png");
    winner = LoadTexture("C:/assets/winner.png");
    soldier1 = LoadTexture("C:/assets/soldier1.png");
    soldier2 = LoadTexture("C:/assets/soldier2.png");
    soldier3 = LoadTexture("C:/assets/soldier3.png");
    soldier4 = LoadTexture("C:/assets/soldier4.png");
    soldier5 = LoadTexture("C:/assets/soldier5.png");
    soldier6 = LoadTexture("C:/assets/soldier6.png");
    soldier10 = LoadTexture("C:/assets/soldier10.png");
    back = LoadTexture("C:/assets/back.png");
    winter = LoadTexture("C:/assets/Zemestan.png");
    spring = LoadTexture("C:/assets/Bahar.png");
    scarecrow = LoadTexture("C:/assets/Matarsak.png");
    drummer = LoadTexture("C:/assets/Tabl_Zan.png");
    virago = LoadTexture("C:/assets/Shir_Zan.png");
    princes = LoadTexture("C:/assets/Shah_Dokht.png");
    dean = LoadTexture("C:/assets/Rish_Sefid.png");
    leader = LoadTexture("C:/assets/Parcham_Dar.png");
    
}

AssetManager::~AssetManager()
{
    UnloadTexture(menu);
    UnloadTexture(info);
    UnloadTexture(game);
    UnloadTexture(map);
    UnloadTexture(table);
    

    UnloadFont(title);
    UnloadFont(listFont);
    UnloadFont(inputFont);
    UnloadFont(askFont);
    UnloadFont(name);

}