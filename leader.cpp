#include <iostream>

#include "leader.h"
#include "player.h"

leaderCard::leaderCard(){}
 void leaderCard::useCard ( std::vector <Player> & players , int numPlayer )
 {
    for(auto player : players)
    {
        player.setPass(true);
    }
 }
