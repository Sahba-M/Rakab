#include <iostream>

#include "purple.h"
#include "spring.h"
#include "player.h"

void SpringCard::setPriority()
{
    priority = 4 ;
}
void SpringCard::useCard ( std::vector <Player> & players , int numPlayer ) 
{
    std::vector <int> indicesPlayers = findMaxPlayer ( players );
    for ( int i = 0 ; i < players.size() ; i++ )
    {
        for ( auto num : indicesPlayers )
        {
            if ( i == indicesPlayers.back() )
            {
                players[i].setScorePlayer (players[i].getScorePlayer() + 3);
                indicesPlayers.pop_back();
            }  
        }
    }
}
std::vector<int> SpringCard::findMaxPlayer ( std::vector <Player> players )
{
    std::vector <int> indices ;
    for ( int i = 0 ; i < players.size() ; i++ )
    {
        if ( findMaxScore (players) == players[i].maxYcards() )
            indices.push_back(i) ;
    }
    return indices ;
}
int SpringCard::findMaxScore ( std::vector <Player> players )
{
    int max = 0 ;
    for ( auto player : players )
    {
        max = player.maxYcards() > max ? player.maxYcards() : max ;
    }
    return max ;
}
