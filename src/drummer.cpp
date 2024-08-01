#include <iostream>

#include "purple.h"
#include "drummer.h"


DrummerCard::DrummerCard(){}

void DrummerCard::useCard ( std::vector <Player> & players , int numPlayer, int number )
{
    int sum = players[numPlayer].getScorePlayer();
    players[numPlayer].setScorePlayer( sum * number );
}
// void DrummerCard::draw ( int x , int y )
// {
//     DrawTexture (myAsset.drummer  , x , y , BLACK);
// }