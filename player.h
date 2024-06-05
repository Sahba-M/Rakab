#include <iostream>
#include <vector>

#include "card.h"

class Player {
    public:
        Player();
        Player ( int age , std::string name , std::string color );
        void setName ( std::string name );
        void setAge ( int age );
        void setColor ( std::string color );
        int getAge() const ;
        void addCard ( Card card );
        void showHandCards ();
        void addProvinces( std::string province );
        void showProvinces();
        int getCardsEachPlayer();
        std::string getName() const ;
        std::string getColor() const ;

    private:
        int age ;
        std::string name ;
        std::string color ;
        std::vector<Card> hand ;
        std::vector<std::string> capturedProvinces;
        int cardsEachPlayer;
        int power;

};