#include "card.h"
#include"player.h"

#ifndef PURPLE_H
#define PURPLE_H


class PurpleCard : public Card {

    public:
    PurpleCard();
    PurpleCard ( std::string name );
    virtual void setPriority() {};
    // virtual void setPower() = 0;
    virtual void useCard ( Player & player ) {};

   protected:
     int priority;


};

#endif 