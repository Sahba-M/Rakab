#include <iostream>
#include <unistd.h>

#include "winter.h"
#include "purple.h"

void WinterCard::setPriority()
{
   priority = 2;
}

void WinterCard::useCard ( std::vector <Player> & players, int numPlayer )
 {
   std:: cout << " use card function ";
   sleep(3);
   // std::cout << "*use winter*" ;
   std::vector<std::shared_ptr<Card>> Ycards = players[numPlayer].getYcards();
   int scores = Ycards.size();  
   for ( int i = 0; i < players.size(); i++ )
   {
      std:: cout << " for use card ";
      sleep(3);
      players[i].setScorePlayer(scores);
   }
 }