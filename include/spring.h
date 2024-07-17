#ifndef SPRING_H
#define SPRING_H

#include <iostream>

#include "purple.h"
#include "control.h"

class SpringCard :public PurpleCard
{
  public:
    virtual void useCard ( std::vector <Player> & players, int numPlayer ) override;
    int findMaxScore ( std::vector <Player> players );//Find the most valuable yellow card among players
    std::vector<int> findMaxPlayer ( std::vector <Player> players );//Find the players with the most valuable cards
  
};

#endif 