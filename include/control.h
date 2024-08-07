#ifndef CONTROL_H
#define CONTROL_H

#include<vector>
#include <memory>

#include "card.h"
#include "player.h"
#include "raylib.h"
#include "input.h"


struct TextButton { //To draw a button
    const char* text;
    Rectangle bounds;
    Color color = BLACK;
    Color buttonColor = {0 , 0 , 0 , 30};
};

struct Textures { //for images
    Texture2D menu ,
              info ,
              game ,
               map ;
};

struct Province {
    Vector2 position;
    Color color;
    std::string name;
};


enum GameScreen { MENU = 0 , NUMBER , INFO , DEAL , MAP , GAME , WINNER }; 

class Control {
    
    public:
        Control(); 
        void setCards(); //Filling vector cards
        void setPlayerNumber ( int playerNumber );
        // void controlNumber(); //Players should be between 3 and 6
        void shuffleCards();
        void getInformation();
        // void showColors();
        void distributeCards();
        // void readProvinces(); //Filling the provinces vector
        // void showUncaptured(); //Showing provinces that have not been captured at all
        void setWar();
        void setPeace( std::string peacePlace );
        void setWarPlace ( std::string warPlace );
        void selectMove ( Player & player,int index );
        // void showPlayGround(); //Show used player cards
        void selectWarPlace ();
        void setProvinceNumber ( int provinceNumber ); //Set the number of game provinces
        // void guideGame(); //Show game guide
        // void guideCards(); //Display guide cards
        void cardAction(); //calculate scores and special cards operation
        void setSeason ( std::string season );
        // void showPurpleCard();
        void run();
        void setDeterminer ( Player & Determiner);
        void setDeterminerPeace ( Player & Determiner);
        void setPlayersReady(); //change to false variable of pass after each round (for all players)
        void burnCards(); //fill the allBurnedCards vector
        void chargeCards();
        void selectPeacePlace();
        // void showAllCaptured();
        void askBurn(); //to burn hand cards of the player who has not got yellow cards
        void findLastDean(); //Find the last player who played dean
        void setIfDean( bool ifDean );
        void setIsLeader(bool isLeader);
        void setIsHorse (bool isHorse ); 
        void updateHorsePlayers();
        void addGameName ( const std::string & fileName ); // to save the name of the files
        void removeGameSaving ( int index ); // to remove file from list
        void saveGame();
        void loadGame();
        bool getIsHorse();
        bool getIsLeader();
        bool changeDeterminerL(); 
        bool getIfDean(); 
        bool changeDeterminer(); 
        bool winGame(Player player);
        bool endEachWar(); //checking that all players pass
        bool winEachWar();
        bool endGame();
        bool ifAllPass();
        bool isBlackCircle();
        bool CompareColors(Color a, Color b);
        int  levenshteinDistance(const std::string &s1, const std::string &s2); // Optimized function to calculate the Levenshtein distance between two strings
        // int  controlAge();
        int  getPlayerNumber();
        int  findPlayerIndex ( Player & player ); //finding the index of determiner to start a new round (for clockwise movement)
        int  getProvinceNumber();
        int  findMaxVirago(); // finding the max number of virago card in playground cards
        // std::string controlColors();
        std::string getWarPlace() const;
        std::string getPeacePlace();
        std::string findClosestMatch(const std::string &input, const std::vector<std::string> &cards, int threshold);
        std::string getSeason();

        std::vector<Player> getPlayers();
        std::vector<Player> maxProvinces(); //Find the players who have captured the most provinces
        std::vector<int> findIndexVirago(); //Find the indices of players who have the most virago card
        Player & getDeterminer();
        Player & getDeterminerPeace();
        Player & youngestPlayer();

        // graphic functions :
        void startGame();
        void setMenuBackground(); //Draw the background image
        void setAskBackground(); // Draw the background image(info) and Back button management
        void setTitle(); // To write the title of the game
        void setMenuList();
        int  getCurrentScreen();
        void Draw();
        void Update();
        void helpButton(); // To click on the help button
        void exitButton(); // To click on the exit button
        void startButton(); // To click on the start button
        void askNumber(); //Select the number of players
        void drawInput(); //To manage user inputs
        void updateInput(); //Getting and updating information
        void askMap();//Draw a map image
        void drawSigns();
        void setGameBackground(); // Draw a picture on the game table
        void initializePlayersColor(); // Initialization to each player's colors
        void changeCircleColor(); //change sign of each player
        bool isColorful(); //To manage the sign of war
        void deal(); //Distribution of cards
        void drawCards();
        void updateCards();
        void managePassButton();
        void determineWinner();//---------------





        void DrawMousePosition();

        void setCurrentIndex(int currentIndex);
        int & getCurrentIndex();
        bool isWhiteCircle();

       


      








        


        
    
    private:
        std::vector<std::shared_ptr<Card>> cards; //A vector of all cards
        std::vector<std::shared_ptr<Card>> allBurnedCards;
        std::vector<std::string> provinces;
        std::vector<Color> colors = { YELLOW, RED , PURPLE , BLUE , GREEN , PINK};
        std::vector<std::string> cardsAndOrdersNames = {"drummer", "princes", "scarecrow", "spring", "winter", "help", "card", "pass"};
        std::vector<std::string> move; // for save move choices of players
        std::vector<Player> players;
        std::vector<int> playersIndices; // for saving indexes of players who pass
        int playerNumber; //The number of players in the game
        int provinceNumber;
        int threshold;
        bool ifDean = false;
        bool isLeader = false;
        bool isHorse = false;
       
        std::string warPlace = "null";
        std::string peacePlace = "null";
        std::string season = "null";
        Player winner; // for winner of each round
        Player DeterminerOfWar; //Determining the location of the battle
        Player DeterminerOfPeace; //Determining the location of the peace place
        std::vector<Player> playerCard;

        std::vector<std::string> files; //files list



        // graphic data members :
        
        GameScreen currentScreen; //enum
        AssetManager myAsset; // an object from AssetManager class
        InputBox inputName { 470 , 160 , 200 , 75 };// an object from InputBox class
        InputBox inputAge { 470 , 245 , 200 , 75 };// an object from InputBox class
        TextButton submit ;//struct
        bool next = false ;
        

        std::vector <TextButton> buttons ;
        std::vector <TextButton> numButtons ;
        std::vector <Color> signColors ;
        std::vector <Province> signs ;
        int provinceIndex;

        bool cardselected = false;
        static int currentIndex ;
        TextButton passButton;
        bool ifDeterminer = true;
        bool ifDeal = true;
       


     
};

#endif