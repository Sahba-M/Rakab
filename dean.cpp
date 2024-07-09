#include "player.h"
#include "dean.h"

void DeanCard::useCard ( std::vector <Player> & players , int numPlayer )
{

}
int DeanCard::findMaxScore ( std::vector <Player> players )
{
    int max = 0 ;
    for ( auto player : players )
    {
        max = player.maxYcards() > max ? player.maxYcards() : max ;
    }
    return max ;
}