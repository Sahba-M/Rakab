#include <iostream>

#include "princes.h"


void PrincesCard::useCard ( std::vector <Player> & players, int numPlayer ) 
{
  players[numPlayer].setScorePlayer(players[numPlayer].getScorePlayer() + 10);
}
