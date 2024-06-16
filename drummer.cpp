#include <iostream>

#include "purple.h"
#include "drummer.h"


DrummerCard::DrummerCard(){}

void DrummerCard::useCard ( std::vector <Player> & players , int numPlayer )
{
    int sum = players[numPlayer].getScorePlayer();
    players[numPlayer].setScorePlayer(sum*2);
}
void DrummerCard::setPriority()
{
    priority = 3;
}