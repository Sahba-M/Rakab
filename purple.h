#include "card.h"

#ifndef PURPLE_H
#define PURPLE_H


class PurpleCard : public Card {

    public:
    PurpleCard ( std::string name );
    // virtual void use();
    // std::string displayName();

    private:
    int priority ;

};

#endif 