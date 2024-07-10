#include "player.h"
#include "dean.h"

void DeanCard::useCard ( std::vector <Player> & players , int numPlayer )
{
    std::vector<int> indicesPlayers = findMaxPlayer ( players );
    for ( auto index : indicesPlayers )
    {
        players[index].setScorePlayer (players[index].getScorePlayer() - findMaxScore(players));
    }
}
std::vector<int> DeanCard::findMaxPlayer ( std::vector <Player> players )
{
    std::vector <int> indices ;
    int max = findMaxScore (players);
    for ( int i = 0 ; i < players.size() ; i++ )
    {
        if ( players[i].maxYcards() == max )
        {
            indices.push_back(i) ;
        }
    }
    return indices ;
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