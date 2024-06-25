#include <iostream>

#include "purple.h"

#ifndef DRUMMER_H
#define DRUMMER_H


class DrummerCard:public PurpleCard
{
  public:
    DrummerCard();
    virtual void useCard ( std::vector <Player> & players, int numPlayer ) override;
};

#endif 