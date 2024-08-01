#include <iostream>
#include <unistd.h>

#include "winter.h"
#include "purple.h"

void WinterCard::useCard ( std::vector <Player> & players , int numPlayer ) //numPlayer is not required here
{
    int scores = 0;
    std::vector<std::shared_ptr<Card>> Ycards;
  
    for ( auto & player : players )
    {
      Ycards = player.getYcards(); //This function returns a vector of yellow cards for each player

      for (int i = 0; i < Ycards.size(); i++)
      {
        scores += (stoi(Ycards[i]->getName())) / 2 ;
      }
       
      player.setScorePlayer(scores);
    }
}  
// void WinterCard::draw ( int x , int y )
// {
//     DrawTexture (myAsset.winter , x , y , BLACK);
// }