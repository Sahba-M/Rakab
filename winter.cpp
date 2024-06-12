#include <iostream>

#include "winter.h"
#include "purple.h"

void Winter::setPriority()
{
   priority = 2;
}

void Winter::useCard ( std::vector <Player> players, int numPlayer = 0  )
 {
    std::vector<std::shared_ptr<Card>> Ycards = players[numPlayer].getYcards();
    int scores = Ycards.size();  
    players[numPlayer].setScorePlayer(scores);
 }