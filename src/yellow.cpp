#include <string>

#include "yellow.h"

YellowCard::YellowCard ( std::string name ) : Card (name) {}

void YellowCard::draw ( int x , int y , AssetManager & myAsset )
{
    if ( name == "1" )
    {
        DrawTexture ( myAsset.soldier1 , x , y , BLACK );
    }
    else if ( name == "2" )
    {
        DrawTexture ( myAsset.soldier2 , x , y , BLACK );
    }
    else if ( name == "3" )
    {
        DrawTexture ( myAsset.soldier3 , x , y , BLACK ); 
    } 
    else if ( name == "4" )
    {
        DrawTexture ( myAsset.soldier4 , x , y , BLACK );
    } 
    else if ( name == "5" )
    {
        DrawTexture ( myAsset.soldier5 , x , y , BLACK );
    } 
    else if ( name == "6" )
    {
        DrawTexture ( myAsset.soldier6 , x , y , BLACK );
    } 
    else if ( name == "10" )
    {
        DrawTexture ( myAsset.soldier10 , x , y , BLACK );
    } 
}
