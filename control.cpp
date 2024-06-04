
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "control.h"
#include "card.h"
#include "purple.h"
#include "yellow.h"

Control::Control() {}

void Control::setPlayerNumber(int playerNumber) 
{
    this->playerNumber = playerNumber;
}
int  Control::getPlayerNumber()
{
    return playerNumber;
}
void Control::controlNumber()
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
    std::string yellowCardType;
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
void Control::showCards()

{
    for ( int i = 0 ; i < cards.size() ; i++ )
    {
        std::cout << cards[i].getName() << std::endl ;
    }
}
void Control::youngestPlayer()
{
    std::string name;
    int age;

    std::vector <std::string> namePlayer;
    std::vector <int> agePlayer;
    std::vector <int> youngestIndices;

    for (int i = 0; i < playerNumber; i++)
    {
        std::cin >> name >> age;
        namePlayer.push_back(name);
        agePlayer.push_back(age);
    }

    int minAge = *min_element(agePlayer.begin(), agePlayer.end());

    for (int i = 0; i < agePlayer.size(); i++) {
        if (agePlayer[i] == minAge) {
            youngestIndices.push_back(i);
        }
    }

    srand(time(0));
    int randomIndex = youngestIndices[rand() % youngestIndices.size()];
    std::cout << "The youngest person is: " << namePlayer[randomIndex] << std::endl;

}
void Control::getInformation()
{
    int age ;
    std::string name ;
    std::string color ;
    for ( int i = 0 ; i < playerNumber ; i++ )
    {
        std::cout << " Player " << i + 1 << " : " << '\n' << " Enter Your Name : " ;
        std::cin >> name ;
        std::cout << '\n' << " Enter Your Age : " ;
        std::cin >> age ;
        std::cout << '\n' << " Enter Your Color : " ;
        std::cin >> color ;
        players.push_back (Player( age , name , color ));
    }
}