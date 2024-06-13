#include <iostream>

#include "purple.h"
#include "drummer.h"


DrummerCard::DrummerCard(){}

void DrummerCard::useCard ( std::vector <Player> & players, int numPlayer )
{
    int sum = 0 ;
    std::vector<int> scores = players[numPlayer].ycardsToInt();
    for ( auto & num : scores )
    {
        sum += num ;
    }
    players[numPlayer].setScorePlayer(sum*2);
}


void DrummerCard::setPriority()
{
    priority = 3;
}