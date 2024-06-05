
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
int Control::getPlayerNumber()
{
    return playerNumber;
}
void Control::controlNumber()
{
    int counter = 0;
    std::cout << " Enter Number Of Your Player : ";
    std::cin >> counter;
    while (counter < 3 || counter > 6)
    {
        system("cls");
        std::cout << " Enter Number Of Your Player : ( ERROR: Please Enter number between 3_6 ) : ";
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
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::shuffle(cards.begin(), cards.end(), generator);
}
void Control::showCards()

{
    for (int i = 0; i < cards.size(); i++)
    {
        std::cout << cards[i].getName() << std::endl;
    }
}
Player Control::youngestPlayer()
{
    // std::vector <std::string> namePlayer;
    std::vector<int> playersAge;
    std::vector<int> youngestIndices;

    for (int i = 0; i < playerNumber; i++)
    {
        playersAge.push_back(players[i].getAge());
    }

    int minAge = *min_element(playersAge.begin(), playersAge.end());

    for (int i = 0; i < playersAge.size(); i++)
    {
        if (playersAge[i] == minAge)
        {
            youngestIndices.push_back(i);
        }
    }

    srand(time(0));
    int randomIndex = youngestIndices[rand() % youngestIndices.size()];
    // std::cout << "The youngest person is: " << players[randomIndex].getName() << std::endl;
    return players[randomIndex];
}
void Control::getInformation()
{
    int age;
    std::string name;
    std::string color;
    for (int i = 0; i < playerNumber; i++)
    {
        std::cout << " Player " << i + 1 << " : " << '\n'
                  << " Enter Your Name : ";
        std::cin >> name;
        std::cout << " Enter Your Age : ";
        std::cin >> age;
        std::cout << " Enter Your Color : ";
        std::cin >> color;
        std::cout << "-----------------------\n";
        players.push_back(Player(age, name, color));
    }
}
void Control::distributeCards(int cardsPerPlayer)
{
    for (int i = 0; i < cardsPerPlayer; i++)
    {
        for (Player &player : players)
        {
            if (!cards.empty())
            {
                player.addCard(cards.back());
                cards.pop_back();
            }
        }
    }
}
void Control::showPlayersHand()
{
    for (int i = 0; i < players.size(); i++)
    {
        std::cout << " Player " << i + 1 << " : " << '\n';
        players[i].showHandCards();
        std::cout << "\n-----------------------\n";
    }
}
void Control::readProvinces()
{
    std::string province;

    std::ifstream inputProvinces;
    inputProvinces.open("map.txt");

    if (!inputProvinces.is_open())
    {
        std::cerr << " Can Not Open File... " << std::endl;
    }
    while (!inputProvinces.eof())
    {
        inputProvinces.ignore();
        inputProvinces >> province;
        provinces.push_back(province);
    }
    inputProvinces.close();
}
void Control::showUncaptured()
{
    for (int i = 0; i < provinces.size(); i++)
    {
        std::cout << provinces[i] << "  ";
    }
}
std::string Control::chosenProvince(Player &player)
{
    bool found = false;
    std::string province;
    std::cout << "\n Unoccupied Provinces Include : ";
    showUncaptured();
    do
    {
        system("cls");
        std::cout << "\n\n " << player.getName() << " Enter Your Chosen Province To War : ";
        std::cin >> province;

        auto elementFound = std::find(provinces.begin(), provinces.end(), province);
        if (elementFound != provinces.end())
        {
            provinces.erase(elementFound);
            found = true;
            return province;
        }
        else
        {
            std::cout << " ERROR: Please Enter Your Desired Province Again : " << std::endl;
            found = false;
        }
    } while (!found);
}

// void getPlayersInClockwiseOrder(std::vector<int>& players, int startingIndex) {
//     int n = players.size();
//     std::vector<int> result(n);

//     for (int i = 0; i < n; i++) {
//         result[(i + 1) % n] = players[(startingIndex + i) % n];
//     }

//     players = result;  
// }