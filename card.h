#include <string>

#ifndef CARD_H
#define CARD_H


class Card {

    public:
    Card( int score );
    Card();
    // virtual void use() = 0 ;

    private:
    int score;
};

#endif 

