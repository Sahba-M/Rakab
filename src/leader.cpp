#include <iostream>

#include "leader.h"
#include "player.h"

LeaderCard::LeaderCard(){}
void LeaderCard::useCard ( std::vector <Player> & players , int numPlayer )
{
    for(auto & player : players)
    {
        player.setPass(true);
    }
}
