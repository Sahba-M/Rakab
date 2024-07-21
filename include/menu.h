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

class MenuGame
{
    public:
    MenuGame();
    ~MenuGame();
    void setBackGround();
    int getScreenWidth();
    int getScreenHeight();
    void setTitle();
    void  setList();
    bool exit ();
    // bool IsClicked (TextButton button);


    private:
        int screenWidth ;
        int screenHeight ;
        std::vector <TextButton> buttons ;

};

#endif 