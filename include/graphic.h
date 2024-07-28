#ifndef MENU_H
#define MENU_H


#include <raylib.h>
#include <vector>
#include "input.h"

#define MAX_INPUT_CHARS 20

struct TextButton {
    const char* text;
    Rectangle bounds;
    Color color = BLACK;
    Color buttonColor = {0 , 0 , 0 , 30};
};

enum GameScreen { MENU = 0 , NUMBER , INFO , GAME }; 

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
    void drawInput();
    void askNumber();
    void getInformation();
    void transferInformation( std::string & inputName, int & inputAge ); 
    void uploadGame();


    private:
        int screenWidth ;
        int screenHeight ;
        int numberofPlayer ;
        bool checkMenu = true;
        std::vector <TextButton> buttons ;
        GameScreen currentScreen;

        InputBox inputName { 600 , 160 , 200 , 75 };
        InputBox inputAge { 600 , 245 , 100 , 75 };
        TextButton submit ;
        bool next = false ;

        std::vector <TextButton> numButtons ;

};

#endif 