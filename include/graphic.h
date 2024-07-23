#ifndef MENU_H
#define MENU_H


#include <raylib.h>
#include <vector>
#define MAX_INPUT_CHARS 20

struct TextButton {
    const char* text;
    Rectangle bounds;
    Color color = BLACK;
    Color buttonColor = {0 , 0 , 0 , 30};
};

enum GameScreen { MENU = 0 , IMAGE }; 

class GraphicGame
{
    public:
    GraphicGame();
    ~GraphicGame();
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
    void setNumberofPlayer(int numberofPlayer);
    int getScreen();
    int getNumberofPlayer();
    void setRecInput();
    void drawInput();
    void askNumber();
    void getInformationG();



    


    private:
        int screenWidth ;
        int screenHeight ;
        int numberofPlayer ;
        bool checkMenu = true;
        std::vector <TextButton> buttons ;
        GameScreen currentScreen;

        char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
        int letterCount = 0;
        Rectangle textBox = { 500, 180, 225, 50 };
        bool mouseOnText = false;
        int framesCounter = 0;

        std::vector <TextButton> numButtons ;

};

#endif 