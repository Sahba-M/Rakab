#ifndef PURPLE_H
#define PURPLE_H

#include "card.h"
#include"player.h"
#include "asset.h"

class PurpleCard : public Card {//The purple class is a parent class

    public:
      PurpleCard();
      PurpleCard ( std::string name );
      virtual void useCard ( std::vector <Player> & players , int ) {};//For the functions of each special card
      // virtual void draw ( int x , int y ) {};


};

#endif 