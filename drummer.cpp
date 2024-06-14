#include <iostream>

#include "purple.h"
#include "drummer.h"


DrummerCard::DrummerCard(){}

void DrummerCard::useCard ( std::vector <Player> & players , int numPlayer )
{
   
    // std::vector<int> scores ;
    // std::vector<std::shared_ptr<Card>> Ycards = players[numPlayer].getYcards();
    // for ( auto & card : Ycards )
    // {
    //     scores.push_back(stoi(card->getName()));
    // }
    // for ( auto & num : scores )
    // {
    //     sum += num ;
    // }
    int sum = players[numPlayer].getScorePlayer();
    players[numPlayer].setScorePlayer(sum*2);
   
}


void DrummerCard::setPriority()
{
    priority = 3;
}