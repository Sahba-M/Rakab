#include "card.h"

#ifndef PURPLE_H
#define PURPLE_H


class PurpleCard : public Card{

    public:
    PurpleCard ( std::string name , int priority , int score );
    // virtual void use();

    private:
    std::string name;
    int priority;

};

#endif 