#include <iostream>

#include "control.h"
#include "card.h"
#include "purple.h"
#include "yellow.h"


Control::Control() 
{ 
    numberOfY1 = 10; 
    numberOfYOther = 8;
}

void Control::setCards()
{

    YellowCard y1card(1);
    YellowCard y2card(2);
    YellowCard y3card(3);
    YellowCard y4card(4);
    YellowCard y5card(5);
    YellowCard y6card(6);
    YellowCard y10card(10);


    for (int i = 0; i < numberOfY1; i++)
    {
        cards.push_back(y1card);
    }

    for ( int i = 0 ; i < numberOfYOther ; i++ )
    {
        cards.push_back(y2card);
        cards.push_back(y3card);
        cards.push_back(y4card);
        cards.push_back(y5card);
        cards.push_back(y6card);
        cards.push_back(y10card);
    }
    std::cout << cards.size();

}