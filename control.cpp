#include <iostream>
#include <fstream>

#include "control.h"
#include "card.h"
#include "purple.h"
#include "yellow.h"

Control::Control() {}

void Control::setCards()
{
    std::ifstream cardInput;
    cardInput.open("yellowCard.txt");
    if (!cardInput.is_open())
    {
        std::cerr << " Can Not Open The File! " << std::endl;
    }
    int cardNumber;
    int yellowCardType;
    while (!cardInput.eof())
    {
        cardInput >> cardNumber >> yellowCardType;
        YellowCard ycard(yellowCardType);
        for (int i = 0; i < cardNumber; i++)
        {
            cards.push_back(ycard);
        }
    }
    cardInput.close();

    cardInput.open("purpleCard.txt");
    if (!cardInput.is_open())
    {
        std::cerr << " Can Not Open The File! " << std::endl;
    }
    std::string purpleCardType;
    while (!cardInput.eof())
    {
        cardInput >> cardNumber >> purpleCardType;
        PurpleCard pcard(purpleCardType);
        for (int i = 0; i < cardNumber; i++)
        {
            cards.push_back(pcard);
        }
    }
    cardInput.close();
}
