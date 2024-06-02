#include <iostream>
#include <fstream>

#include "control.h"
#include "card.h"
#include "purple.h"
#include "yellow.h"


Control::Control(){}

void Control::setCards ()
{
    std::ifstream cardInput ;
    cardInput.open("cards.txt");
    if ( !cardInput.is_open() )
    {
        std::cerr << " Can Not Open The File! " << std::endl ;
    }
    int cardNumber ;
    int cardType ;

    while (cardInput)
    {
        cardInput >> cardNumber >> cardType ;
        YellowCard ycard(cardType) ;
        for ( int i=0 ; i < cardNumber ; i++ )
        {
            cards.push_back(ycard);
        }
    }
    
}