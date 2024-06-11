#include "card.h"
#include"player.h"

#ifndef PURPLE_H
#define PURPLE_H


class PurpleCard : public Card {

    public:
      PurpleCard ( std::string name );
      virtual void setPriority() {};
      virtual void useCard ( Player & player ) {};

   protected:
     int priority;


};

#endif 