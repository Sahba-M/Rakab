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