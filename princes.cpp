#include <iostream>

#include "princes.h"


void Princes::setPriority() 
{
   priority = 5;
}
void useCard ( std::vector <Player> players, int numPlayer ) 
{
  players[numPlayer].setScorePlayer(players[numPlayer].getScorePlayer() + 10);
}
