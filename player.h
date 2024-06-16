#include <iostream>
#include <vector>
#include <memory>

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
        void setSeason(std::string season);
        void setPass( bool pass );
        void setScorePlayer ( int scorePlayer );
        void addCard (  std::shared_ptr<Card> card );
        void showHandCards();
        void addProvinces( std::string province );
        void showProvinces();
        void selectCard ();
        void showUsedCards();
        void showYcard();
        void recognizeYellow();
        void yellowInScore();
        void burnCardsPlayer();
        void showCapturedProvinces();
        void burnHand();
        int  getAge() const ;
        int  getScorePlayer();
        int  getHandSize();
        int  getNumProvinces();
        int  numCardsOfPlayer(); //For the number of cards during distribution
        int  maxYcards();
        int  numberOfPrinces();
        bool isFind ( std::shared_ptr<Card> Ycard ); //Find the yellow card
        bool hasDrummer();
        bool hasPrinces();
        bool getPass();
        bool hasYellowCard();
        bool hasPurpleCard();
        bool ifBurn();
        bool winGame();
        std::string getName() const ;
        std::string getColor() const ;
        std::string getSeason();
        std::vector<std::shared_ptr<Card>> getYcards();
        std::vector<std::shared_ptr<Card>> & getBurnedCards();
        std::vector<std::shared_ptr<Card>> & getHandCards();




    private:
        int age ;
        std::string name ;
        std::string color ;
        std::vector<std::shared_ptr<Card>> hand ; //cards in hand
        std::vector<std::shared_ptr<Card>> usedCards ; //Cards on the floor
        std::vector<std::shared_ptr<Card>> yellowCards;
        std::vector<std::shared_ptr<Card>> burnedCards;
        std::vector<std::string> capturedProvinces;

        int cardsEachPlayer;
        int scorePlayer;
        std::string season;
        bool pass = false;


};
#endif  