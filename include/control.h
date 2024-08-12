#ifndef CONTROL_H
#define CONTROL_H

#include<vector>
#include <memory>

#include "card.h"
#include "player.h"
#include "raylib.h"
#include "input.h"
#include "map.h"



struct TextButton // to draw a button
{ 
    const char* text;
    Rectangle bounds;
    Color color = BLACK;
    Color buttonColor = {0 , 0 , 0 , 30};
};
struct Province // for save information of provinces
{
    Vector2 position;
    Color color;
    std::string name;
};

enum GameScreen { MENU = 0 , NUMBER , INFO , DEAL , MAP , GAME , WINNER , ASKBURN , END }; // manage game

class Control
{
    public:
        Control(); 
        void setCards(); //Filling vector cards
        void setPlayerNumber ( int playerNumber );
        void shuffleCards();
        void getInformation();
        void distributeCards();
        void readProvinces(); //Filling the provinces vector
        void setPeace( std::string peacePlace );
        void setWarPlace ( std::string warPlace );
        void selectWarPlace ();
        void setProvinceNumber ( int provinceNumber ); //Set the number of game provinces
        void cardAction(); //calculate scores and special cards operation
        void setSeason ( std::string season );
        void setDeterminer ( Player & Determiner);
        void setDeterminerPeace ( Player & Determiner);
        void setPlayersReady(); //change to false variable of pass after each round (for all players)
        void burnCards(); //fill the allBurnedCards vector
        void chargeCards();
        void selectPeacePlace();
        void askBurn( int number ); //to burn hand cards of the player who has not got yellow cards
        void setIfDean( bool ifDean );
        void setIsLeader(bool isLeader);
        void updateHorsePlayers();
        bool getIsLeader();
        bool changeDeterminerL(); 
        bool getIfDean(); 
        bool changeDeterminer(); 
        bool winGame(Player player);
        bool endEachWar(); //checking that all players pass
        bool winEachWar();
        bool endGame();
        bool checkAllBurn();
        int  getPlayerNumber();
        int  findPlayerIndex ( Player & player ); //finding the index of determiner to start a new round (for clockwise movement)
        int  getProvinceNumber();
        int  findMaxVirago(); // finding the max number of virago card in playground cards
        int  getCurrentIndex();
        std::string getWarPlace() const;
        std::string getPeacePlace();
        std::string getSeason();
        std::vector<Player> maxProvinces(); //Find the players who have captured the most provinces
        std::vector<int> findIndexVirago(); //Find the indices of players who have the most virago card
        Player & getDeterminer();
        Player & getDeterminerPeace();
        Player & youngestPlayer();

        void saveGame();
        void loadGame();
        void removeGameSaving ( int index ); // to remove file from list
        void addGameName ( const std::string & fileName ); // to save the name of the files


        // graphic functions :


        void startGame();
        void setMenuBackground(); // Draw the background image
        void setAskBackground(); // Draw the background image(info) and Back button management
        void setTitle(); // To write the title of the game
        void setMenuList();
        void Draw();  
        void Update();
        void helpButton(); // To click on the help button
        void exitButton(); // To click on the exit button
        void startButton(); // To click on the start button
        void loadButton(); // To click on the load button
        void askNumber(); //Select the number of players
        void drawInput(); //To manage user inputs
        void updateInput(); //Getting and updating information
        void askMap();//Draw a map image
        void drawSigns(); // to show provinces signs
        void setGameBackground(); // Draw a picture on the game table
        void changeCircleColor(); //change sign of each player
        void deal(); //Distribution of cards
        void drawCards();
        void updateCards();
        void managePassButton();
        void determineWinner();
        void setCurrentIndex(int currentIndex);
        void playersNotYellow();
        void showEnd();
        bool isWhiteCircle();
        bool isBlackCircle();
        bool CompareColors(Color a, Color b);
        int  getCurrentScreen();   
        GameScreen readState( int number ); // to read the current screen
    
    private:
        std::vector<std::shared_ptr<Card>> cards; //A vector of all cards
        std::vector<std::shared_ptr<Card>> allBurnedCards;
        std::vector<std::string> provinces;
        std::vector<Color> colors = { YELLOW , RED , PURPLE , BLUE , GREEN , PINK };
        std::vector<std::string> files; //files list
        std::vector<Player> players;
        std::vector<int> playersIndices; // for saving indexes of players who pass
        int playerNumber; //The number of players in the game
        int provinceNumber;
        bool ifDean = false;
        bool isLeader = false;
        std::string warPlace = "null";
        std::string peacePlace = "null";
        std::string season = "null";
        Player winner; // for winner of each round
        Player DeterminerOfWar; //Determining the location of the battle
        Player DeterminerOfPeace; //Determining the location of the peace place


        // graphic data members :
        
        GameScreen currentScreen; // enum
        AssetManager myAsset; // an object from AssetManager class
        Map map;
        InputBox inputName { 470 , 160 , 200 , 75 }; // an object from InputBox class
        InputBox inputAge { 470 , 245 , 200 , 75 }; // an object from InputBox class
        TextButton submit ; // struct
        std::vector <TextButton> buttons ;
        std::vector <TextButton> numButtons ;
        std::vector <Color> signColors ;
        std::vector <Province> signs ;
        std::vector <Player> noYellowPlayers ;
        std::vector <Player> winnerPlayers ;
        static int currentIndex;
        int provinceIndex;
        TextButton passButton;
        bool cardselected = false;
        bool ifDeterminer = true;
        bool ifDeal = true;
        bool next = false;
};
#endif