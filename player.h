#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "card.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
    public:
        Player();
        Player ( int age , std::string name , std::string color );
        void setName ( std::string name );
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
        int  getAge() const ;
        int  getScorePlayer();
        int  getHandSize(); //The number of cards in the player's hand
        int  getNumProvinces(); //The number of provinces captured by the player
        int  numCardsOfPlayer(); //For the number of cards during distribution
        int  maxYcards(); //Find the most valuable yellow card player
        int  numberOfPrinces(); //The number of princes cards used by the player
        int  numberOfVirago(); //The number of virago cards used by the player
        int  numberOfDean(); //The number of dean cards used by the player
        bool isFind ( std::shared_ptr<Card> Ycard ); //Find the yellow card and return it to the player's hand
        bool hasDrummer(); //Having a drummer card in the player's used cards
        bool hasPrinces(); //Having a princes card in the player's used cards
        bool hasVirago(); //Having a virago card in the player's used cards
        bool hasDean(); //Having a dean card in the player's used cards
        bool getPass();
        bool hasYellowCard(); //Having yellow cards in the player's hand
        bool hasPurpleCard(); //Having purple cards in the player's hand
        bool ifBurn(); //Does the player want to burn her hand if she doesn't have yellow cards?
        bool isProximity();

       // bool winGame(); //Determine the winner of the game
        std::string getName() const ;
        std::string getColor() const ;
        std::string getSeason();
        std::vector<std::shared_ptr<Card>> getYcards();
        std::vector<std::shared_ptr<Card>> & getBurnedCards();
        std::vector<std::shared_ptr<Card>> & getHandCards();

    private:
        std::string season;
        std::string name ;
        std::string color ;
        std::vector<std::shared_ptr<Card>> hand ; //cards in hand
        std::vector<std::shared_ptr<Card>> usedCards ; //Cards on the floor
        std::vector<std::shared_ptr<Card>> yellowCards; //Yellow cards for each player
        std::vector<std::shared_ptr<Card>> burnedCards; //Burned player cards
        std::vector<std::string> capturedProvinces; //The player's captured provinces
        int age ;
        int scorePlayer;
        bool pass = false;
};
#endif  