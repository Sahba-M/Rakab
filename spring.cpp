#include <iostream>

#include "purple.h"
#include "spring.h"

void SpringCard::setPriority()
{
    priority = 4;
}
void useCard ( Player & player ) 
{
    std::vector<int> scores ;
    std::vector<std::shared_ptr<Card>> Ycards = player.getYcards();

     for ( auto & card : Ycards )
    {
        scores.push_back(stoi(card->getName()));
    }
    
}