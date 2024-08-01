#include "virago.h"
#include "player.h"


void ViragoCard::useCard ( std::vector <Player> & players , int numPlayer )
{
    players[numPlayer].setScorePlayer(players[numPlayer].getScorePlayer() + 1);
}
// void ViragoCard::draw ( int x , int y )
// {
//     DrawTexture (myAsset.virago , x , y , BLACK);
// }