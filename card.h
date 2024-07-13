#include <string>

#ifndef CARD_H
#define CARD_H

class Card { //The card class is a parent class

     friend std::istream &operator>> (std::istream &input, Card &card);

   
    public:
        Card( std::string name );
        Card();
        virtual ~Card();
        void setName(std::string name);
        std::string getName();
        bool operator== (const Card & other);
  
    private:
        std::string name;
};
#endif 

