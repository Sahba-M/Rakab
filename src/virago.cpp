#include "virago.h"
#include "player.h"


void ViragoCard::useCard ( std::vector <Player> & players , int numPlayer )
{
    players[numPlayer].setScorePlayer(players[numPlayer].getScorePlayer() + 1);
}
