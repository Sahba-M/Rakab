#include <iostream>

#include "horse.h"
#include "player.h"

HorserCard::HorserCard(){}

void HorserCard::useCard ( std::vector <Player> & players , int numPlayer )
{
    for(auto &player : players)
    {
        player.setPass(true);
    }
}
