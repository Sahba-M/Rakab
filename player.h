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
        std::string getName() const ;
        std::string getColor() const ;
        int  getAge() const ;
        void addCard (  std::shared_ptr<Card> card );
        void showHandCards();
        void addProvinces( std::string province );
        void showProvinces();
        void selectCard ();
        void showUsedCards();
        int  getCardsEachPlayer(); //For the number of cards during distribution
        void showYcard();
        bool isFind ( std::shared_ptr<Card> Ycard ); //Find the yellow card
        std::vector<std::shared_ptr<Card>> getYcards();
        void setScorePlayer ( int scorePlayer );
        int  getScorePlayer();
        void recognizeYellow();
        int maxYcards();
        void setSeason(std::string season);
        std::string getSeason();
        bool hasDrummer();
        bool hasPrinces();
        int numberOfPrinces();
        int getHandSize();
        void setPass( bool pass );
        bool getPass();
        bool hasYellowCard();
        void yellowInScore();
        bool ifBurn();

    private:
        int age ;
        std::string name ;
        std::string color ;
        std::vector<std::shared_ptr<Card>> hand ; //cards in hand
        std::vector<std::shared_ptr<Card>> usedCards ; //Cards on the floor
        std::vector<std::shared_ptr<Card>> yellowCards;
        std::vector<std::string> capturedProvinces;

        int cardsEachPlayer;
        int scorePlayer;
        std::string season = "deafult";
        bool pass = false;


};
#endif  