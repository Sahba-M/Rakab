#include "card.h"

#ifndef PURPLE_H
#define PURPLE_H


class PurpleCard : public Card {

    public:
    PurpleCard ( std::string name );
    virtual void setPriority() = 0;
    virtual void setPower() = 0;

    
    // virtual void use();
    // std::string displayName();

   protected:
    int priority;
    int power;

    private:

};

#endif 