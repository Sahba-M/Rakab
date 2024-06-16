#include <string>

#ifndef CARD_H
#define CARD_H


class Card {

    public:
        Card( std::string name , int score = 0 );
        Card();
        virtual ~Card();
        void setScore(int score);
        void setName(std::string name);
        int getScore();
        std::string getName();
        bool operator== (const Card & other);
  
    private:
        int score;
        std::string name;
};

#endif 

