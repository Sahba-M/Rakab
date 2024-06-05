#include <iostream>

#include "player.h"

class Player {
    public:
        Player();
        Player ( int age , std::string name , std::string color );
        void setName ( std::string name );
        void setAge ( int age );
        void setColor ( std::string color );
        int getAge() const ;
        std::string getName() const ;
        std::string getColor() const ;
        void addCard ( Card card );
        void showHandCards ();

    private:
        int age ;
        std::string name ;
        std::string color ;
        std::vector<Card> hand ;

};