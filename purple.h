#include "card.h"
#include"player.h"

#ifndef PURPLE_H
#define PURPLE_H


class PurpleCard : public Card {

    public:
    PurpleCard ( std::string name );
    virtual void setPriority() = 0;
    // virtual void setPower() = 0;
    virtual void useCard ( Player & player ) = 0;

   protected:
    int priority;

    private:

};

#endif 