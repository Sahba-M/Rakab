#include "player.h"
#include "dean.h"

DeanCard::DeanCard(){}

void DeanCard::useCard ( std::vector <Player> & players , int numPlayer )
{
    std::vector<int> indicesPlayers = findMaxPlayer ( players );
    for ( auto index : indicesPlayers )
    {
        players[index].setScorePlayer (players[index].getScorePlayer() - (players[index].numberOfMaxYcards() * findMaxScore(players)));
    }
}
std::vector<int> DeanCard::findMaxPlayer ( std::vector <Player> players )
{
    std::vector <int> indices ;
    int max = findMaxScore (players);

   
    for ( int i = 0 ; i < players.size() ; i++ )
    {
        if ( players[i].hasYellowGround() )
        {
            if ( players[i].maxYcards() == max )
            {
                indices.push_back(i) ;
            }
        } 
    }
    return indices ;
}
int DeanCard::findMaxScore ( std::vector <Player> players )
{
    int max = 0 ;
    
    for ( int i = 0; i < players.size(); i++)
    {
        if ( players[i].hasYellowGround() )
        {
            std::cout << players[i].getName() << std::endl;
             max = players[i].maxYcards() > max ? players[i].maxYcards() : max ;  
        }
    }
    return max ;
}

