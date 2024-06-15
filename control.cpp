
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
#include <unordered_map>

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
void Control::setCards() // read cards
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
    std::random_device randomDevice;        // A class for generating random numbers
    std::mt19937 generator(randomDevice()); // random number generator (seed)
    std::shuffle(cards.begin(), cards.end(), generator);
}
Player &Control::youngestPlayer()
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
            std::cout << std::endl
                      << " Enter Your Chosen Color: ";

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
        std::cout << " Player " << i + 1 << " : " << '\n'
                  << " Enter Your Name : ";

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
    for ( Player & player : players )
    {
        std::cout << " I Want To Give The Cards To  _" << player.getName() << "_  Please Give Him/Her The System \n";
        for (int i = 0 ; i < player.numCardsOfPlayer() ; i++)
        {
            if (!cards.empty())
            {
                player.addCard(cards.back()); // It is added to the hand
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
    std::string province, ignore;
    std::ifstream inputProvinces;
    inputProvinces.open("map.txt");
    setProvinceNumber(14);

    if (!inputProvinces.is_open())
    {
        std::cerr << " Can Not Open File... " << std::endl;
    }
    for (int i = 0; i < getProvinceNumber(); i++)
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
void Control::setWar()
{
    
    selectWarPlace(getDeterminer());
    int startIndex = findPlayerIndex(DeterminerOfWar);
    int currentIndex = startIndex ;
    system("cls");
    while (!endEachWar())
    {
        for ( int i = 0 ; i < getPlayerNumber()  ; i++ )
        {
            showAllCaptured();
            showPlayGround();
            std::cout << "\n\n The War Is Over " << warPlace << "\n\n ";
            selectMove(players[currentIndex], currentIndex);
            currentIndex = (currentIndex + 1) % players.size();
            system("cls");
        }
    }
    cardAction();
    if (winEachWar())
    {
        std::cout << " >>> " << winner.getName() << " <<< " <<  " Is The Winner Of This Round!!! \n ";
        sleep(5);
        std::cout << warPlace << " is warPlace " ;
        auto elementFound = std::find(provinces.begin(), provinces.end(), warPlace);
        if (elementFound != provinces.end())
        provinces.erase(elementFound);
        std::cout << " after erasing ..." ;
        setDeterminer(winner);
        
    }
    else 
    {
        std::cout << " This War Has No Winners!!! ";
        sleep(5);
        setDeterminer(players[playersIndices.back()]);
    }

    for (int i = 0; i < getPlayerNumber(); i++)
    {
        move[i] = "temp";
    }
    
}
void Control::setDeterminer ( Player & Determiner )
{
    DeterminerOfWar = Determiner;
}
Player & Control::getDeterminer()
{
    return DeterminerOfWar;
}
void Control::selectMove(Player & player, int index)
{
    move.resize(playerNumber , "temp");
    char choice ;
   
    if (move[index] != "pass" && player.getHandSize() != 0 )
    {
        std::cout << " " << player.getName() << " Please Choose Your Movement ( pass / card / help ): ";
        std::cin >> move[index];

        if (move[index] == "card")
        {
            std::cout << " ";
            player.showHandCards();
            player.recognizeYellow();
            player.selectCard();
            if ((player.getSeason() == "winter" || player.getSeason() == "spring"))
            setSeason(player.getSeason()); 
            
        }
        else if (move[index] == "help")
        {
            system("cls");
            int selection;
            std::cout << " 1. Game  Guide \n";
            std::cout << " 2. Cards Guide \n\n";
            std::cout << " YOUR CHOICE: ";
            std::cin >> selection;
            if (selection == 1)
            {
                guideGame();
                choice = getch();
                system("cls");
                showPlayGround();
                selectMove(player, index);
            }
            else if (selection == 2)
            {
                guideCards();
                choice = getch();
                system("cls");
                showPlayGround();
                selectMove(player, index);
            }
        }
        else
        {
            std::cout << " ERROR : Invalid Move... \n ";
            selectMove(player, index);
        }
    }
    else
    {
        playersIndices.push_back(index);
        player.setPass(true);
    }
}
void Control::showPlayGround()
{
    std::cout << "---------------------\n";
    for (int i = 0; i < players.size(); i++)
    {
        players[i].showUsedCards();
    }
    std::cout << "---------------------\n";
}
void Control::selectWarPlace(Player &player)
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
        std::cin >> chooseProvince;

        auto elementFound = std::find(provinces.begin(), provinces.end(), chooseProvince);

        if (elementFound != provinces.end())
        {
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
    this->provinceNumber = provinceNumber;
}
int Control::getProvinceNumber()
{
    return provinceNumber;
}
bool Control::winEachWar()
{
    int winnerIndex ;
    int max = 0;
    std::vector<Player> winPlayers;
    for (auto player : players)
    {
        max = player.getScorePlayer() > max ? player.getScorePlayer() : max;
    }
    for (int j = 0; j < getPlayerNumber(); j++)
    {
        if (max == players[j].getScorePlayer())
        {
            winPlayers.push_back(players[j]);
            winnerIndex = j ;
        }
    }
    if (winPlayers.size() == 1)
    {
        winner = winPlayers[0];
        players[winnerIndex].addProvinces(warPlace);
        return true;
    }
    else
    {
        return false;
    }
}
std::vector<Player> Control::getPlayers()
{
    return players;
}
void Control::guideGame()
{
    std::ifstream inputGuide;
    std::string explanation;
    inputGuide.open("guide.txt");
    if (!inputGuide.is_open())
    {
        std::cerr << " Can Not Open File... " << std::endl;
    }
    system("cls");
    std::cout << " ------------------------------------------------- \n"
              << std::setw(13) << " << HELP PAGE >> \n\n";
    while (std::getline(inputGuide, explanation))
    {
        std::cout << explanation << std::endl;
    }
    std::cout << " \n\n ------------------------------------------------- \n";
    inputGuide.close();
}
void Control::guideCards()
{
    std::ifstream inputGuides;
    std::string cardName, cardDescription, requestedCard;
    std::unordered_map<std::string, std::string> card;

    inputGuides.open("cardGuide.txt");
    if (!inputGuides.is_open())
    {
        std::cerr << " Can Not Open File... \n"
                  << std::endl;
    }
    while (inputGuides >> cardName >> std::ws && std::getline(inputGuides, cardDescription))
    {
        card[cardName] = cardDescription;
    }
    inputGuides.close();

    showPurpleCard();
    std::cout << "\n Please Enter The Name Of The Card You Want: ";
    std::cin >> requestedCard;

    if (card.find(requestedCard) != card.end())
    {
        std::cout << "\n ------> " << card[requestedCard] << " <------ " << std::endl;
    }
    else
    {
        std::cout << " Card Not Found! " << std::endl;
    }
}
void Control::showPurpleCard()
{
    std::vector<std::string> purpleCards = {"Scarecrow", "Drummer", "Princes", "Winter", "Spring"};
    std::cout << "\n ------------------------------------------- \n ";
    for (auto card : purpleCards)
    {
        std::cout << card << "  ";
    }
    std::cout << "\n ------------------------------------------- \n\n ";
}
void Control::cardAction()
{
    for ( int i = 0 ; i < playerNumber ; i++ )
    {
        players[i].yellowInScore();
    }

    WinterCard winter;
    SpringCard spring;
    DrummerCard drummer;
    PrincesCard prince;
    // winter -- drummer -- spring -- princes

   
    if (season == "winter")
    {
        winter.useCard(players, -1);
    }

    for (int i = 0; i <  getPlayerNumber(); i++)
    {
        if (players[i].hasDrummer())
        {
            drummer.useCard(players, i);
        }
    }

    if (season == "spring")
        spring.useCard(players, -1);

    for (int i = 0; i < getPlayerNumber(); i++)
    {
        if (players[i].hasPrinces())
        {
            for (int j = 0; j < players[i].numberOfPrinces(); j++)
            {
                prince.useCard(players, i);
            }
        }
    }
}
void Control::setSeason(std::string season)
{
    this->season = season;
}
bool Control::endEachWar()
{
    bool flag = false;
    for (auto player : players)
    {
        if (player.getPass() == true)
        {
            flag = true;
        }
        else
        {
            flag = false;
            break;
        }
    }
    return flag;
}
void Control::setPlayersReady()
{
    for ( auto & player : players )
    {
        player.setPass(false);
    } 
}
bool Control::endGame()
{
    std::vector<Player> gamePlayers;
    if ( provinces.size() == 0 )
    {
       std::vector<Player> tempPlayer = maxProvinces();
       for (int i = 0; i < tempPlayer.size(); i++)
       {
          std::cout << " _ { " << tempPlayer[i].getName() << " } " << " IS WINER... \n ";
       }  
       return true;  
    } else
    {
        for( auto & player : players)
        {
            if (player.winGame())
            {
               gamePlayers.push_back(player);
            }   
        }
        system("cls");
        for (int i = 0; i < gamePlayers.size(); i++)
        {
            std::cout << " _ { " << gamePlayers[i].getName() << " } " << " IS WINER... \n ";
        }

        if ( gamePlayers.size() != 0 )
            return true;
        else 
            return false;
    } 
}
int Control::findPlayerIndex ( const Player & player ) 
{
    for ( int i = 0 ; i < players.size() ; i++ ) 
    {
        if ( players[i].getName() == player.getName() ) {
            return i ;
        }
    }
    return -1; // player not found
}
void Control::run()
{
    setDeterminer( youngestPlayer());
    while (!endGame())
    {
        std::cout << " while run ";
        setPlayersReady();
        setWar();
        burnCards();
    }
    std::cout << "after while ";

}
std::vector<Player> Control::maxProvinces()
{
    std::vector<Player> maxProvinces;
    int max = 0;
    for (int i = 0; i < players.size(); i++)
    {
       max = players[i].getNumProvinces() > max ? players[i].getNumProvinces() : max;
    }
    for (int i = 0; i < players.size(); i++)
    {
       if (max == players[i].getNumProvinces())
       {
            maxProvinces.push_back(players[i]);
       }  
    }
    return maxProvinces;
}
void Control::burnCards()
{
    for ( auto & player : players )
    {
        player.burnCardsPlayer(); 
        allBurnedCards.insert(allBurnedCards.end(), player.getBurnedCards().begin(), player.getBurnedCards().end());
    }
}
void Control::chargeCards()
{
    int counter = 0 ;
    for ( int i = 0 ; i < getPlayerNumber() ; i++ )
    {
        if ( players[i].getHandSize() != 0 )
        {
            counter++ ;
        }
    }
    if ( counter == 0 || counter == 1 )
    {
        burnCards();
        for ( auto & player : players )
        {
            player.burnHand();
            allBurnedCards.insert(allBurnedCards.end(), player.getHandCards().begin(), player.getHandCards().end());
        }
    }
    cards.insert(cards.end(), allBurnedCards.begin(), allBurnedCards.end());
    shuffleCards();
    distributeCards();
}
void Control::showAllCaptured()
{
    std::cout << " The Captured Privinces Is : \n ";
    std::cout << " --------------------------- \n";
    for (int i = 0; i < getPlayerNumber(); i++)
    {
        players[i].showCapturedProvinces();
    }
    std::cout << " --------------------------- \n\n";


    
}

