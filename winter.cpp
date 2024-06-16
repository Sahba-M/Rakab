#include <iostream>
#include <unistd.h>

#include "winter.h"
#include "purple.h"

void WinterCard::setPriority()
{
   priority = 2;
}
void WinterCard::useCard ( std::vector <Player> & players , int numPlayer )
 {
   int scores;
   std::vector<std::shared_ptr<Card>> Ycards;
   for ( auto & player : players )
   {
      Ycards = player.getYcards();
      scores = Ycards.size();  
      player.setScorePlayer(scores);
   }
 }