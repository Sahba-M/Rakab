#include <iostream>

#include "winter.h"
#include "purple.h"

void Winter::setPriority()
{
   priority = 2;
}

void useCard ( Player & player )
 {
    std::vector<std::shared_ptr<Card>> Ycards = player.getYcards();
    int scores = Ycards.size();  
    player.setScorePlayer(scores);
 }