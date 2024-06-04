#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>

#include "control.h"
#include "card.h"
#include "purple.h"
#include "yellow.h"

Control::Control() {}

void Control::setPlayerNumber(int playerNumber) 
{
    this->playerNumber = playerNumber;
}
int Control::getPlayerNumber()
{
    return playerNumber;
}
void Control:: controlNumber()
{
    int counter = 0;
    while (counter < 3 || counter > 6)
    {
        system("cls");
        std::cout << " Enter Number Of Your Player : ( Please Enter number between 3_6 )";
        std::cin >> counter;
    }
    setPlayerNumber(counter);
    getPlayerNumber();
}
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
void Control::shuffleCards()
{
    std::random_device randomDevice ;
    std::mt19937 generator(randomDevice());
    std::shuffle(cards.begin(), cards.end(), generator);
}
