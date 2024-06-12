#include<iostream>

#include "yellow.h"
#include "purple.h"
#include"scarecrow.h"

ScarecrowCard::ScarecrowCard (){}
void ScarecrowCard::useCard ( std::vector <Player> players, int numPlayer = 0  )
{
    bool found = false;
    std::string selectYcard;
    players[numPlayer].showYcard();
    // system("cls");
    std::cout << "\n" << players[numPlayer].getName() << " Which Card Do You Want To Remove? : ";
    std::cin >> selectYcard;
    std::shared_ptr<Card> card = std::make_shared<YellowCard>(selectYcard);
    while (!players[numPlayer].isFind(card))
    {
        std::cout << " Enter Valid Card : " ;
        std::cin >> selectYcard;
        card = std::make_shared<YellowCard>(selectYcard);
    } 
}