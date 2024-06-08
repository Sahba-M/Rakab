
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
void Control::setColor()
{
   this-> colors = {"RED", "YELLOW", "GREEN", "BLUE", "PURPLE", "PINK"};
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
std::string Control::controlColors()
{
    bool found = true;
    std::string chooseColor;
    do
    {
        std::cout << "\n ";
        for (int i = 0; i < colors.size(); i++)
        {
            std::cout << colors[i] << " ~ ";
        }
        if (found == true)
            std::cout << std::endl
                      << " Enter Your Chosen Color: ";
        std::cin >> chooseColor;

        auto elementFound = std::find(colors.begin(), colors.end(), chooseColor);

        if (elementFound != colors.end())
        {
            colors.erase(elementFound);
            found = true;

            return chooseColor;
        }
        else
        {
            std::cout << " \n ERROR: Please Enter Your Color Again : " << std::endl;
            found = false;
        }
    } while (!found);
    return " ";
}
void Control::getInformation()
{
    int age;
    std::string name;
    std::string color;
    for (int i = 0; i < playerNumber; i++)
    {
        std::cout << " Player " << i + 1 << " : " << '\n' << " Enter Your Name : ";
                 
        std::cin >> name;
        std::cout << " Enter Your Age : ";
        std::cin >> age;
       // setColor();
        color = controlColors();
        std::cout << "-----------------------\n";
        players.push_back(Player(age, name, color));
    }
}
void Control::distributeCards()
{
    std::cin.ignore();
    for (Player &player : players)
    {

        std::cout << " I Want To Give The Cards To  _" << player.getName() << "_  Please Give Him/Her The System \n";
        for (int i = 0; i < player.getCardsEachPlayer(); i++)
        {
            if (!cards.empty())
            {
                player.addCard(cards.back());
                cards.pop_back();
            }
        }

        std::cin.ignore();
        player.showHandCards();

        std::cin.ignore();
        system("cls");
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
    return " ";
}
void Control::test()
{
    std::string temp;
    for (Player &player : players)
    {
        std::cout << player.getName() << " Please Choose Card : \n";
        player.showHandCards();
        std::cout << '\n'
                  << " Your Choose : ";
        // std::cin >> temp;
        // Card c(temp);
        player.useCard();
        std::cout << '\n';
        player.showUsedCards();
    }
}

// void getPlayersInClockwiseOrder(std::vector<int>& players, int startingIndex) {
//     int n = players.size();
//     std::vector<int> result(n);

//     for (int i = 0; i < n; i++) {
//         result[(i + 1) % n] = players[(startingIndex + i) % n];
//     }

//     players = result;
// }