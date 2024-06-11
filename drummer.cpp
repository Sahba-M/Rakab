#include <iostream>

#include "purple.h"
#include "drummer.h"


DrummerCard::DrummerCard(){}

void DrummerCard::useCard ( Player & player )
{
    int sum = 0 ;
    std::vector<int> scores ;
    std::vector<std::shared_ptr<Card>> Ycards = player.getYcards();
    for ( auto & card : Ycards )
    {
        scores.push_back(stoi(card->getName()));
    }
    for ( auto & num : scores )
    {
        sum += num ;
    }
    player.setScorePlayer(sum);
}


void DrummerCard::setPriority()
{
    priority = 3;
}