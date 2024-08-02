#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <raylib.h>
#include <vector>
#include <memory>
#include <string>

#include "card.h"

class Player {

    friend std::istream & operator>> (std::istream &input , Player &player );
    friend std::ostream & operator<< ( std::ostream & output , Player & player );

    public:
        Player();
        Player ( int age , const char* name , std::string color);
        void setName ( const char* name );
        void setAge ( int age );
        void setColor ( std::string color );
        void setSeason ( std::string season ); //To control spring and winter
        void setPass( bool pass ); //Player passing control
        void setScorePlayer ( int scorePlayer );
        void addCard ( std::shared_ptr<Card> card ); //Add a card to the player's hand
        void showHandCards(); //Show the cards in the player's hand
        void addProvinces ( std::string province ); //Add player captured provinces
        void selectCard (); //Card selection by the player
        void showUsedCards(); //Show the player's played cards
        void showYcard(); //Show the yellow cards used by the player
        void recognizeYellow(); //Detection of yellow cards used by players
        void yellowInScore(); //Calculation of player's yellow card points
        void burnCardsPlayer(); //Add used cards to burned cards
        void showCapturedProvinces();
        void burnHand(); //Add hand cards to burned cards
        void insertBurnedCard ( std::vector<std::shared_ptr<Card>> & cards );
        void insertHandCard ( std::vector<std::shared_ptr<Card>> & cards );
        void setIfLeader(bool ifLeader);
        void setIfHorse(bool ifHorse);
        int  getAge() const ;
        int  getScorePlayer();
        int  getHandSize(); //The number of cards in the player's hand
        int  getNumProvinces(); //The number of provinces captured by the player
        int  numCardsOfPlayer(); //For the number of cards during distribution
        int  maxYcards(); //Find the most valuable yellow card player
        int  numberOfPrinces(); //The number of princes cards used by the player
        int  numberOfDrummer(); //The number of drummer cards used by the player
        int  numberOfVirago(); //The number of virago cards used by the player
        int  numberOfMaxYcards(); //The number of max cards used by the player
        // int  numberOfDean(); //The number of dean cards used by the player
        bool isFind ( std::shared_ptr<Card> Ycard ); //Find the yellow card and return it to the player's hand
        bool hasDrummer(); //Having a drummer card in the player's used cards
        bool hasPrinces(); //Having a princes card in the player's used cards
        bool hasVirago(); //Having a virago card in the player's used cards
        bool hasDean(); //Having a dean card in the player's used cards
        bool hasHorse();
        bool getPass();
        bool hasYellowGround();
        bool hasYellowCard(); //Having yellow cards in the player's hand
        bool hasPurpleCard(); //Having purple cards in the player's hand
        bool ifBurn(); //Does the player want to burn her hand if she doesn't have yellow cards?
        bool isProximity();
        bool getIfLeader();
        bool getIfHorse();
        std::string getColor() const ;
        std::string getSeason();
        std::vector<std::shared_ptr<Card>> getYcards();
        
        //-----------------grafic functions---------------------------
        const char * getName() ;
        void setColorG(Color graficColor);
        Color getColorG();
        void drawCards( int x , int y ,  AssetManager & myAsset, Vector2 origin, float rotation);
        void drawCardSpecialPlayer(int x, int y, AssetManager &myAsset, Vector2 origin, float rotation);//For players who are vertical!
        void drawBackCards(int x, int y, AssetManager &myAsset, Vector2 origin, float rotation);
        void drawBackCardSpecialPlayer(int x, int y, AssetManager &myAsset, Vector2 origin, float rotation);//For players who are vertical!



        

    private:
        std::string season;
        char name[256] ;
        std::string color ;
        std::vector<std::shared_ptr<Card>> hand ; //cards in hand
        std::vector<std::shared_ptr<Card>> usedCards ; //Cards on the floor
        std::vector<std::shared_ptr<Card>> yellowCards; //Yellow cards for each player
        std::vector<std::shared_ptr<Card>> burnedCards; //Burned player cards
        std::vector<std::string> capturedProvinces; //The player's captured provinces
        int age ;
        int scorePlayer;
        bool pass = false;
        bool ifLeader = false;
        bool ifHorse = false;
        Color graficColor;
        // AssetManager myAsset;
};
#endif  