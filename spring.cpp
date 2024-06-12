#include <iostream>

#include "purple.h"
#include "spring.h"

void SpringCard::setPriority()
{
    priority = 4;
}
void SpringCard::useCard ( std::vector <Player> players, int numPlayer = 0  ) 
{
    std::vector<int> scores ;
    std::vector<std::shared_ptr<Card>> Ycards = players[numPlayer].getYcards();

     for ( auto & card : Ycards )
    {
        scores.push_back(stoi(card->getName()));
    }
    
}
