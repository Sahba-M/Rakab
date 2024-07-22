#ifndef MENU_H
#define MENU_H


#include <raylib.h>
#include <vector>

struct TextButton {
    const char* text;
    Rectangle bounds;
    Color color = BLACK;
    Color buttonColor = {0 , 0 , 0 , 30};
};

enum GameScreen { MENU = 0 , IMAGE }; 

class MenuGame
{
    public:
    MenuGame();
    ~MenuGame();
    void setBackGround();
    int getScreenWidth();
    int getScreenHeight();
    void setTitle();
    void setList();
    bool exit ();
    void help();
    void start();
    void setCheckMenu(bool checkMenu);
    bool getCheckMenu();
    void setImage();
    int getScreen();
    


    private:
        int screenWidth ;
        int screenHeight ;
        std::vector <TextButton> buttons ;
        bool checkMenu = true;
        GameScreen currentScreen;

};

#endif 