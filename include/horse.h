#ifndef HORSE_H
#define HORSE_H

#include <iostream>

#include "purple.h"

class HorserCard :public PurpleCard{
     
     public:
        HorserCard();
        virtual void useCard ( std::vector <Player> & players , int numPlayer ) override;

};

#endif 