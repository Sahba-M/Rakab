
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <conio.h>

#include "control.h"
#include "card.h"
#include "purple.h"
#include "yellow.h"
#include "winter.h"
#include "spring.h"
#include "drummer.h"
#include "princes.h"
#include "player.h"

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
}
void Control::setCards() //read cards
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
        for (int i = 0; i < cardNumber; i++)
        {
            cards.push_back(std::make_shared<YellowCard>(yellowCardType));
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
        for (int i = 0; i < cardNumber; i++)
        {
            cards.push_back(std::make_shared<PurpleCard>(purpleCardType));
        }
    }
    cardInput.close();
}
void Control::shuffleCards()
{
    std::random_device randomDevice; //A class for generating random numbers
    std::mt19937 generator(randomDevice());//random number generator (seed)
    std::shuffle(cards.begin(), cards.end(), generator);
}
Player Control::youngestPlayer()
{

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
void Control::showColors()
{
    std::cout << "\n ";
    for (int i = 0; i < colors.size(); i++)
        {
            std::cout << colors[i] << " ~ ";
        }
}
std::string Control::controlColors()
{
    bool found = true;
    std::string chooseColor;
    do
    {
        showColors();
        if (found == true)
            std::cout << std::endl << " Enter Your Chosen Color: ";
                      
        std::cin >> chooseColor;

        auto elementFound = std::find(colors.begin(), colors.end(), chooseColor);

        if (elementFound != colors.end())
        {
            colors.erase(elementFound);
            found = true;
            break; 
        }
        else
        {
            std::cout << " \n ERROR: Please Enter Your Color Again : " << std::endl;
            found = false;
        }
    } while (!found);
    return chooseColor;
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

        color = controlColors();
        std::cout << "-----------------------\n";
        players.push_back(Player(age, name, color));
    }
    system("cls");
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
                player.addCard(cards.back());//It is added to the hand
                cards.pop_back();
            }
        }

        std::cin.ignore();
        player.showHandCards();

        std::cin.ignore();
        system("cls");
    }
}
void Control::readProvinces()
{
    std::string province , ignore;
    std::ifstream inputProvinces;
    inputProvinces.open("map.txt");
    setProvinceNumber(14);

    if (!inputProvinces.is_open())
    {
        std::cerr << " Can Not Open File... " << std::endl;
    }
    for ( int i = 0 ; i < getProvinceNumber() ; i++ )
    {
        inputProvinces >> ignore;
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

void Control::test()
{
    selectWarPlace(players[0]);
    system("cls");
    for (int i = 0 ; i < 10 ; i++)
    {
        for ( Player & player : players )
        {
            showPlayGround();
            std::cout << " The War Is Over " << warPlace << '\n' ;
            selectMove(player);
            system("cls");
        }
    }
    
    // std::string temp;
    // for (Player &player : players)
    // {
    //     std::cout << player.getName() << " Please Choose Card : \n";
    //     player.showHandCards();
    //     std::cout << '\n'
    //               << " Your Choose : ";
    //     // std::cin >> temp;
    //     // Card c(temp);
    //     player.selectCard();
    //     std::cout << '\n';
    //     player.showUsedCards();
    // }
}
void Control::selectMove(Player & player)
{
    std::string move;
    char choice;
    std::cout << " " << player.getName() << " Please Choose Your Movement ( pass / card / help ): "; 
    std::cin >> move;

    if (move == "pass")
    {
      /* code */
      
    } else if(move == "card")
    {
        std::cout << " " ;
        player.showHandCards();
        player.selectCard();
        setSeason (player.getSeason());
    } else if (move == "help")
    {
      guideGame();
      choice = getch() ;
      system("cls");
      showPlayGround();
      selectMove(player);
    } 
    else
    {
       std::cout << " ERROR : Invalid Move... ";
       selectMove(player);
    }
}
void Control::showPlayGround()
{
    std::cout << "---------------------\n" ;
    for (int i = 0; i < players.size(); i++)
    {
        players[i].showUsedCards();
    }
    std::cout << "---------------------\n" ;
    
}
void Control::selectWarPlace (Player & player)
{
    bool found = true;
    std::string chooseProvince;
    do
    {
        std::cout << "\n ";
        for (int i = 0; i < provinces.size(); i++)
        {
            std::cout << provinces[i] << " ~ ";
        }
        std::cout << std::endl;
        if (found == true)
            std::cout << " " << player.getName() << " Enter Your Chosen Province: ";
        std::cin >> chooseProvince ;

        auto elementFound = std::find(provinces.begin(), provinces.end(), chooseProvince);

        if (elementFound != provinces.end())
        {
            provinces.erase(elementFound);
            found = true;
            break;
        }
        else
        {
            std::cout << " \n ERROR: Please Enter Your Province Again : " << std::endl;
            found = false;
        }
    } while (!found);
    warPlace = chooseProvince;
}
void Control::setProvinceNumber(int provinceNumber)
{
    this -> provinceNumber = provinceNumber;
}
int Control::getProvinceNumber()
{
    return provinceNumber;
}
// void getPlayersInClockwiseOrder(std::vector<int>& players, int startingIndex) {
//     int n = players.size();
//     std::vector<int> result(n);

//     for (int i = 0; i < n; i++) {
//         result[(i + 1) % n] = players[(startingIndex + i) % n];
//     }

//     players = result;
// }
std::vector<Player> Control::getPlayers()
{
    return players;
}
void Control::guideGame()
{
    std::ifstream inputGuide;
    std::string explanation;
    if (!inputGuide.is_open())
    {
        std::cerr << " Can Not Open File... " << std::endl;
    }
    inputGuide.open("guide.txt");
    system("cls");
    std::cout << " ------------------------------------------------- \n" << std::setw(13) << " << HELP PAGE >> \n\n"; 
    while (std::getline(inputGuide,explanation))
    {
       std::cout << explanation << std::endl;
    }
    std::cout << " \n\n ------------------------------------------------- \n"; 
    inputGuide.close();  
}
void Control::cardAction()
{
    WinterCard winter ;
    SpringCard spring ;
    DrummerCard drummer ;
    PrincesCard prince ;
    // winter -- drummer -- spring -- princes 
    if ( season == "winter" )
        winter.useCard(players , -1);
    
    for ( int i = 0 ; i < playerNumber ; i++ )
    {
        if ( players[i].hasDrummer() )
        drummer.useCard ( players , i );
    }

    if ( season == "spring" )
        spring.useCard(players , -1);

    for ( int i = 0 ; i < playerNumber ; i++ )
    {
        if(players[i].hasPrinces())
          {
             for (int j = 0; j < players[i].numberOfPrinces(); j++)
                 {
                        prince.useCard(players , i);
                 }
         } 
    }

}
void Control::setSeason ( std::string season )
{
    this -> season = season ;
}
