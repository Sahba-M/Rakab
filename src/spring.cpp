#include <iostream>

#include "purple.h"
#include "spring.h"
#include "player.h"


void SpringCard::useCard ( std::vector <Player> & players , int numPlayer ) 
{
    std::vector<int> indicesPlayers = findMaxPlayer ( players );
    for ( auto index : indicesPlayers )
    {
        players[index].setScorePlayer (players[index].getScorePlayer() + 3);
    }
}
std::vector<int> SpringCard::findMaxPlayer ( std::vector <Player> players )
{
    std::vector <int> indices ;
    int max = findMaxScore (players);

    for ( int i = 0 ; i < players.size() ; i++ )
    {
        if (players[i].hasYellowGround())
        {
            if ( players[i].maxYcards() == max )
            {
                indices.push_back(i) ;
            }  
        }
        else if (players[i].hasPrinces())
        {
            indices.push_back(i);
        }
        
    }
    return indices ;
}
int SpringCard::findMaxScore ( std::vector <Player> players )
{
    int max = 0 ;
    for ( auto player : players )
    {
        if (player.hasPrinces())
        {
            max = 10;
        } else
        {
            if (player.hasYellowGround())
            {
                max = player.maxYcards() > max ? player.maxYcards() : max ;
            }
        }
    }
    return max ;
}
void SpringCard::draw ( int x , int y , AssetManager & myAsset )
{
    DrawTexture (myAsset.spring , x , y , BLACK);
}