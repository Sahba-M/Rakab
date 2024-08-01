#include<iostream>

#include "yellow.h"
#include "purple.h"
#include"scarecrow.h"

ScarecrowCard::ScarecrowCard (){}
void ScarecrowCard::useThisCard ( Player & player )
{
    bool found = false;
    std::string selectYcard;
    
    player.showYcard();
    std::cout << "\n" << player.getName() << " Which Card Do You Want To Remove? : ";
    std::cin >> selectYcard;
    
    std::shared_ptr<Card> card = std::make_shared<YellowCard>(selectYcard);
    while (!player.isFind(card))//If this yellow card was not on the field
    {
        std::cout << " Enter Valid Card : " ;
        std::cin >> selectYcard;
        card = std::make_shared<YellowCard>(selectYcard);
    } 
}
void ScarecrowCard::draw ( int x , int y )
{
    DrawTexture (myAsset.scarecrow , x , y , BLACK);
}