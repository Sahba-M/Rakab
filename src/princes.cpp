#include <iostream>

#include "princes.h"


void PrincesCard::useCard ( std::vector <Player> & players, int numPlayer ) 
{
  players[numPlayer].setScorePlayer(players[numPlayer].getScorePlayer() + 10);
}
void PrincesCard::draw ( int x , int y )
{
    DrawTexture (myAsset.princes , x , y , BLACK);
}