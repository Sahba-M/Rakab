#include <iostream>

#include "princes.h"

#ifndef PRINCES_H
#define PRINCES_H

void PrincesCard::useCard ( std::vector <Player> & players, int numPlayer ) 
{
  players[numPlayer].setScorePlayer(players[numPlayer].getScorePlayer() + 10);
}
#endif