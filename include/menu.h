#ifndef MENU_H
#define MENU_H


#include <raylib.h>

class MenuGame
{
    public:
    MenuGame();
    ~MenuGame();
    void setBackGround();
    int getScreenWidth();
    int getScreenHeight();
    void setTitle();


    private:
        int screenWidth ;
        int screenHeight ;

};

#endif 