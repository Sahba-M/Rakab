#include <iostream>
#include <unistd.h>

#include "winter.h"
#include "purple.h"

void WinterCard::useCard ( std::vector <Player> & players , int numPlayer )//numPlayer is not required here
 {
   int scores;
   std::vector<std::shared_ptr<Card>> Ycards;
   for ( auto & player : players )
   {
      Ycards = player.getYcards(); //This function returns a vector of yellow cards for each player
      scores = Ycards.size();  
      player.setScorePlayer(scores);
   }
 }