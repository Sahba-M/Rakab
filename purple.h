#include "card.h"
#include"player.h"

#ifndef PURPLE_H
#define PURPLE_H


class PurpleCard : public Card {

    public:
      PurpleCard();
      PurpleCard ( std::string name );
      virtual void setPriority() {};
      virtual void useCard ( std::vector <Player> & players , int ) {};

   protected:
     int priority;

};

#endif 