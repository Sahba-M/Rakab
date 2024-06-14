#include <iostream>

#include "winter.h"
#include "purple.h"

void WinterCard::setPriority()
{
   priority = 2;
}

void WinterCard::useCard ( std::vector <Player> & players , int numPlayer )
 {
   std::cout << "*use winter*" ;
   int scores;
   std::vector<std::shared_ptr<Card>> Ycards;
   for ( auto player : players )
   {
      std::cout << "if winter use" ;
      Ycards = player.getYcards();
      scores = Ycards.size();  
      std::cout << "^^^^^^size^^^^^^" << scores << std::endl;
      player.setScorePlayer(scores);
      std::cout << player.getScorePlayer() << " ----- " ;
   }
 }