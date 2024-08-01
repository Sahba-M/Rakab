#include <iostream>

#include "leader.h"
#include "player.h"

LeaderCard::LeaderCard(){}
 void LeaderCard::useCard ( std::vector <Player> & players , int numPlayer )
 {
    for(auto &player : players)
    {
        player.setPass(true);
    }
 }
//  void LeaderCard::draw ( int x , int y )
// {
//     DrawTexture (myAsset.leader , x , y , BLACK);
// }
