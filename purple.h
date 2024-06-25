#include "card.h"
#include"player.h"

#ifndef PURPLE_H
#define PURPLE_H


class PurpleCard : public Card {//The purple class is a parent class

    public:
      PurpleCard();
      PurpleCard ( std::string name );
      virtual void useCard ( std::vector <Player> & players , int ) {};//For the functions of each special card
};

#endif 