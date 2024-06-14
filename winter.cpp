#include <iostream>

#include "winter.h"
#include "purple.h"

void WinterCard::setPriority()
{
   priority = 2;
}

void WinterCard::useCard ( std::vector <Player> & players, int numPlayer )
 {
   // std::cout << "*use winter*" ;
   std::vector<std::shared_ptr<Card>> Ycards = players[numPlayer].getYcards();
   int scores = Ycards.size();  
   for ( auto player : players )
   {
      players[numPlayer].setScorePlayer(scores);
   }
 }