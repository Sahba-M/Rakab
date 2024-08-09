#ifndef DRUMMER_H
#define DRUMMER_H

#include <iostream>

#include "purple.h"

class DrummerCard:public PurpleCard
{
  public:
    DrummerCard();
    void useCard ( std::vector <Player> & players, int numPlayer , double number );
   
};
#endif 
