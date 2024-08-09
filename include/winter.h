#ifndef WINTER_H
#define WINTER_H

#include<iostream>

#include "purple.h"


class WinterCard : public PurpleCard
{
  public:
      virtual void useCard ( std::vector <Player> & players, int numPlayer ) override;
   
};
#endif