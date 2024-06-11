#include<iostream>

#include "yellow.h"
#include "purple.h"
#include"scarecrow.h"

ScarecrowCard::ScarecrowCard (){}
void ScarecrowCard::useCard ( Player & player )
{
    bool found = false;
    std::string selectYcard;
    player.showYcard();
    // system("cls");
    std::cout << "\n" << player.getName() << " Which Card Do You Want To Remove? : ";
    std::cin >> selectYcard;
    std::shared_ptr<Card> card = std::make_shared<YellowCard>(selectYcard);
    while (!player.isFind(card))
    {
        std::cout << " Enter Valid Card : " ;
        std::cin >> selectYcard;
        card = std::make_shared<YellowCard>(selectYcard);
    } 
}