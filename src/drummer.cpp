#include "purple.h"
#include "drummer.h"


DrummerCard::DrummerCard(){}

void DrummerCard::useCard ( std::vector <Player> & players , int numPlayer , double number )
{
    int sum = players[numPlayer].getScorePlayer();
    players[numPlayer].setScorePlayer( sum * number );
}
