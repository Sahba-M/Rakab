#include <string>

#ifndef CARD_H
#define CARD_H

class Card {//The card class is a parent class

    public:
        Card( std::string name );
        Card();
        void setName(std::string name);
        std::string getName();
        bool operator== (const Card & other);
  
    private:
        int score;
        std::string name;
};
#endif 

