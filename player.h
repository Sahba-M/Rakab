#include <iostream>
#include <vector>
#include <memory>

#include "card.h"

class Player {
    public:
        Player();
        Player ( int age , std::string name , std::string color );
        void setName ( std::string name );
        void setAge ( int age );
        void setColor ( std::string color );
        int getAge() const ;
        void addCard (  std::shared_ptr<Card> card );
        void showHandCards();
        void addProvinces( std::string province );
        void showProvinces();
        void selectCard ();
        void showUsedCards();
        int getCardsEachPlayer();
        std::string getName() const ;
        std::string getColor() const ;
        void showYcard();
        bool isFind ( std::shared_ptr<Card> Ycard );

    private:
        int age ;
        std::string name ;
        std::string color ;
        std::vector<std::shared_ptr<Card>> hand ;
        std::vector<std::shared_ptr<Card>> usedCards ;
        std::vector<std::string> capturedProvinces;
        std::vector<std::shared_ptr<Card>> yellowCard;

        int cardsEachPlayer;
        int power;

};