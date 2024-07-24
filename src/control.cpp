
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
#include <climits>
#include <math.h>

#include "control.h"
#include "card.h"
#include "purple.h"
#include "yellow.h"
#include "winter.h"
#include "spring.h"
#include "drummer.h"
#include "princes.h"
#include "virago.h"
#include "dean.h"
#include "player.h"
#include "map.h"
#include "leader.h"

Control::Control()
{
    provinceNumber = 15;
    int threshold = 3;
}

void Control::setPlayerNumber(int playerNumber)
{
    this->playerNumber = playerNumber;
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
void Control::setCards()
{
    std::ifstream cardInput;
    cardInput.open("../src/yellowCard.txt");
    if (!cardInput.is_open())
    {
        std::cerr << " Can Not Open The File! " << std::endl;
    }
    int cardNumber; // Number of yellow cards
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

    cardInput.open("../src/purpleCard.txt");
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
void Control::showColors()
{
    std::cout << "\n ";
    for (int i = 0; i < colors.size(); i++)
    {
        std::cout << colors[i] << " ~ ";
    }
}
void Control::getInformation()
{
    int age;
    std::string name;
    std::string color;
    for (int i = 0; i < getPlayerNumber(); i++)
    {
        std::cout << " Player " << i + 1 << " : " << '\n' << " Enter Your Name : ";
                 
        std::cin.ignore();
        std::getline(std::cin, name);


        // std::cout << " Enter Your Age : ";
        // std::cin >> age;
        age = controlAge();

        color = controlColors();
        std::cout << "-----------------------\n";
        players.push_back(Player(age, name, color)); // Fill vector of players
    }
    system("cls");
}
void Control::distributeCards()
{
    std::cin.ignore();
    for (Player &player : players)
    {
        std::cout << " I Want To Give The Cards To  > " << player.getName() << " <  Please Give Him/Her The System \n";
        for (int i = 0; i < player.numCardsOfPlayer(); i++)
        {
            if (!cards.empty())
            {
                player.addCard(cards.back()); // Gives the last vector card to the player
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
    setProvinceNumber(provinceNumber);

    inputProvinces.open("../src/map.txt");
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
    LeaderCard leader;
    
    if (getIfDean())
    {
        selectPeacePlace(getDeterminerPeace());
        setIfDean(false);
    }
    selectWarPlace(getDeterminer());

    int startIndex = findPlayerIndex(getDeterminer());
    int currentIndex = startIndex;
    system("cls");
    
    while (!endEachWar())
    {
        for (int i = 0; i < getPlayerNumber(); i++)
        {
            showAllCaptured();
            showPlayGround();
            std::cout << "\n The War Is Over => " << getWarPlace() << "\n\n ";
            selectMove(players[currentIndex], currentIndex);
            if (players[currentIndex].getIfLeader())
            {
                leader.useCard(players,-1);
                setIsLeader(true);
                system("cls");
                std::cout << "end if leader \n";
                sleep(2);
                break;
            }
            currentIndex = (currentIndex + 1) % players.size();
            system("cls");

            saveGame(); // save the game
        }
    }
    cardAction();
    if (winEachWar())
    {
        std::cout << " >>> " << winner.getName() << " <<< " << " Is The Winner Of This Round!!! \n\n ";
        sleep(5);
        auto elementFound = std::find(provinces.begin(), provinces.end(), getWarPlace());
        if (elementFound != provinces.end())
               provinces.erase(elementFound);

        if (!changeDeterminerL())
        {
            if (!changeDeterminer())
            {
               setDeterminer(winner);
            }
        }
    }
    else
    {
        std::cout << " This War Has No Winners!!! ";
        sleep(5);
        if (!changeDeterminerL())
        {
             if (!changeDeterminer())
             {
                 setDeterminer(players[playersIndices.back()]); // set the last player who pass the game
             } 
        } 
    }

    for (int i = 0; i < getPlayerNumber(); i++) // to update move vector from "pass" to "temp"
    {
        move[i] = "temp";
        players[i].setSeason("temp");
    }

    saveGame();
    
}
void Control::setDeterminer(Player &Determiner)
{
    DeterminerOfWar = Determiner;
}
void Control::setDeterminerPeace(Player &Determiner)
{
    DeterminerOfPeace = Determiner;
}
void Control::selectMove(Player &player, int index)
{
    move.resize(getPlayerNumber(), "temp"); // Filling the initial value of move vector with "temp"
    char choice;

    if (move[index] != "pass" && player.getHandSize() != 0)
    {
        std::cout << " " << player.getName() << " Please Choose Your Movement ( pass / card / help ): ";
        std::cin >> move[index];
        std::string closestMatch = findClosestMatch(move[index], cardsAndOrdersNames, threshold);

        if (!closestMatch.empty() && closestMatch != move[index])
        {
            std::cout << "Did you mean " << closestMatch << "? (yes/no): ";
            std::string response;
            std::cin >> response;
            //????????????????????????????????????????????????????
        }
        if (move[index] == "card")
        {
            std::cout << " ";
            player.showHandCards();
            player.recognizeYellow(); // update yellowCard vector
            player.selectCard();
            playerCard.push_back(player);

            if ((player.getSeason() == "winter" || player.getSeason() == "spring")) // the season set here
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
                showAllCaptured();
                showPlayGround();
                selectMove(player, index);
            }
            else if (selection == 2)
            {
                guideCards();
                choice = getch();
                system("cls");
                showAllCaptured();
                showPlayGround();
                selectMove(player, index);
            }
        }
        else
        {
            std::cout << " ERROR : Invalid Move... ";
            selectMove(player, index);
        }
    }
    else // if pass
    {
        playersIndices.push_back(index);
        player.setPass(true);
    }
}
void Control::showPlayGround()
{
    std::cout << "--------------------------- \n";
    for (int i = 0; i < players.size(); i++)
    {
        players[i].showUsedCards();
    }
    std::cout << "--------------------------- \n";
}
void Control::selectWarPlace(Player &player)
{
    bool found = true;
    std::string chooseProvince;
    do
    {
        std::cout << "\n ";
        std::cout << "---------------------------------------------------------------------------------------------------------\n ";
        for (int i = 0; i < provinces.size(); i++)
        {
            std::cout << provinces[i] << "  ";
        }
        std::cout << "\n ---------------------------------------------------------------------------------------------------------\n\n\n ";
        std::cout << std::endl;

        if (found == true)
            std::cout << " " << player.getName() << " Enter Your Chosen Province: ";
        std::cin >> chooseProvince;

        if ( chooseProvince == getPeacePlace())
        {
            std::cout << " You Can Not Choose This province ; Because It is Peace Place ." << std::endl;
            found = false;
        }
        else
        {
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
        }
    } while (!found);

    setWarPlace(chooseProvince);
}
void Control::selectPeacePlace(Player &player)
{
    bool found = true;
    std::string chooseProvince, response = "null";

    std::cout << "\n ";
    std::cout << "---------------------------------------------------------------------------------------------------------\n ";
    for (int i = 0; i < provinces.size(); i++)
    {
        std::cout << provinces[i] << "  ";
    }
    std::cout << "\n ---------------------------------------------------------------------------------------------------------\n\n\n ";
    std::cout << std::endl;
    std::cout << " " << player.getName() << " Do You Want To Determine The Peace Place? (Y/N) ";
    std::cin >> response;

    if (response == "Y")
    {
        do
        {
            if (found == true)
            {
                std::cout << " Enter Your Choosen Province : ";
                std::cin >> chooseProvince;
            }
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

        setPeace(chooseProvince);
    }         
}
void Control::setWarPlace(std::string warPlace)
{
    this->warPlace = warPlace;
}
void Control::setProvinceNumber(int provinceNumber)
{
    this->provinceNumber = provinceNumber;
}
void Control::guideGame()
{
    std::ifstream inputGuide;
    std::string explanation;
    inputGuide.open("../src/guide.txt");
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
    inputGuides.open("../src/cardGuide.txt");
    if (!inputGuides.is_open())
    {
        std::cerr << " Can Not Open File... \n" << std::endl;
                 
    }
    while (inputGuides >> cardName >> std::ws && std::getline(inputGuides, cardDescription))
    {
        card[cardName] = cardDescription;
    }
    inputGuides.close();
    showPurpleCard();
    std::cout << "\n Please Enter The Name Of The Card You Want: ";
    std::cin >> requestedCard;
    while (card.find(requestedCard) == card.end())
    {
        std::cout << "\n Please Enter Again: ";
        std::cin >> requestedCard;
    }
    std::cout << "\n ------> " << card[requestedCard] << " <------ " << std::endl;
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
    // The priority of the cards is: dean - winter - drummer - spring - princes , virago
    for (int i = 0; i < getPlayerNumber(); i++) // filling up the scores related to the yellow cards
    {
        players[i].yellowInScore();
    }
    WinterCard winter;
    SpringCard spring;
    DrummerCard drummer;
    PrincesCard prince;
    ViragoCard virago;
    DeanCard dean;
    

    for (int i = 0; i < getPlayerNumber(); i++)
    {
        if (players[i].hasDean())
        {
            dean.useCard(players, i);
            setIfDean(true);
        }
    }                                                      
    if (season == "winter")
    {
        winter.useCard(players, -1);
    }
    for (int i = 0; i < getPlayerNumber(); i++)
    {
        if (players[i].hasDrummer())
        {
            double calcuteNumber = pow (1.5, players[i].numberOfDrummer());
            drummer.useCard(players,i, calcuteNumber);
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
    for (int i = 0; i < getPlayerNumber(); i++)
    {
        if (players[i].hasVirago())
        {
            for (int j = 0; j < players[i].numberOfVirago(); j++)
            {
                virago.useCard(players, i);
            }
        }
    }
    findLastDean();
    setSeason("temp");
}
void Control::setSeason(std::string season)
{
    this->season = season;
}
void Control::setPlayersReady()
{
    for (auto &player : players)
    {
        player.setPass(false);
    }
}
void Control::run()
{
    Map map;
    map.readMatrix();
    map.readUnorderedMap();
    setCards();
    shuffleCards();
    controlNumber();
    getInformation();
    distributeCards();
    readProvinces();
    setDeterminer(youngestPlayer());
    while (!endGame())
    {
        setPlayersReady();
        setWar();
        askBurn();
        burnCards();
        chargeCards();
    }
}
void Control::burnCards()
{
    for (auto &player : players)
    {
        player.burnCardsPlayer();
        player.insertBurnedCard (allBurnedCards);  // for all player
        // allBurnedCards.insert(allBurnedCards.end(), player.getBurnedCards().begin(), player.getBurnedCards().end()); // for all player
    }
}
void Control::chargeCards()
{
    int counter = 0;
    for (int i = 0; i < getPlayerNumber(); i++)
    {
        if (players[i].getHandSize() != 0) // check if the card is finish or not
        {
            counter++;
        }
    }
    if (counter == 0 || counter == 1)
    {
        burnCards();
        for (auto &player : players)
        {
            player.burnHand();
            player.insertHandCard (allBurnedCards); 
            // allBurnedCards.insert(allBurnedCards.end(), player.getHandCards().begin(), player.getHandCards().end());

        }
        cards.insert(cards.end(), allBurnedCards.begin(), allBurnedCards.end());
        shuffleCards();
        distributeCards();
    }
}
void Control::showAllCaptured()
{
    std::cout << " The Captured Provinces Is : \n";
    std::cout << "\n";
    for (int i = 0; i < getPlayerNumber(); i++)
    {
        players[i].showCapturedProvinces();
    }
    std::cout << "\n\n";
}
void Control::askBurn()
{
    for (auto &player : players)
    {
        if (player.ifBurn())
        {
            player.burnHand();
        }
        system("cls");
    }
}
void Control::setPeace(std::string peacePlace)
{
    this->peacePlace = peacePlace;
}
void Control::setIfDean( bool ifDean )
{
   this -> ifDean = ifDean; 
}
bool Control::getIfDean()
{
    return ifDean;
}
bool Control::changeDeterminer()
{
    std::vector<int> indices = findIndexVirago();
    if (indices.size() == 1)
    {
        setDeterminer(players[indices[0]]);
        return true;
    }
    return false;
}
bool Control::changeDeterminerL()
{
    if (getIsLeader())
    {
        setIsLeader(false);
        setDeterminer(playerCard[playerCard.size() - 2]);

        for(auto &player : players)
        {
            player.setPass(false);
            player.setIfLeader(false);
        }
        return true;
    }
    return false; 
}

int Control::getPlayerNumber()
{
    return playerNumber;
}
int Control::findPlayerIndex(const Player &player)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].getName() == player.getName())
        {
            return i;
        }
    }
    return -1; // player not found
}
int Control::getProvinceNumber()
{
    return provinceNumber;
}
int Control::controlAge()
{
    int chooseAge;
    bool res = false;
    while (!res)
    {
        std::cout << " Enter Your Valid Age : ";
        std::cin >> chooseAge;
        if (chooseAge > 0)
            res = true;
    }
    return chooseAge;
}
int Control::levenshteinDistance(const std::string &s1, const std::string &s2)
{
    int m = s1.size();
    int n = s2.size();
    if (m == 0)
        return n; // If one of the strings is empty
    if (n == 0)
        return m;
    std::vector<int> prevRow(n + 1), currRow(n + 1); // Create two vectors to store distances for the current and previous rows
    for (int j = 0; j <= n; ++j)
    { // Initialize the previous row
        prevRow[j] = j;
    }
    for (int i = 1; i <= m; ++i)
    {
        currRow[0] = i;
        for (int j = 1; j <= n; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                currRow[j] = prevRow[j - 1];
            }
            else
            {
                currRow[j] = 1 + std::min({prevRow[j], currRow[j - 1], prevRow[j - 1]});
            }
        }
        prevRow = currRow;
    }
    return currRow[n];
}
int Control::findMaxVirago()
{
    int max = 0;
    for (auto player : players)
    {
        max = player.numberOfVirago() > max ? player.numberOfVirago() : max;
    }
    return max;
}
bool Control::endGame()
{
    std::vector<Player> gamePlayers;
    if (provinces.size() == 0)
    {
        std::vector<Player> tempPlayer = maxProvinces();
        for (int i = 0; i < tempPlayer.size(); i++)
        {
            std::cout << "  { " << tempPlayer[i].getName() << " } " << " IS WINER :) \n ";
        }
        return true;
    }
    for (auto &player : players)
    {
        if (winGame(player))
        {
            gamePlayers.push_back(player);
        }
    }
    system("cls");
    for (int i = 0; i < gamePlayers.size(); i++)
    {
        std::cout << " _ { " << gamePlayers[i].getName() << " } " << " IS WINER ... \n ";
    }
    if (gamePlayers.size() != 0) // to check we have winner or not
        return true;
    else
        return false;
}
bool Control::winGame(Player player)
{
    if (player.isProximity() || player.getNumProvinces() == 5)
    {
        return true;
    }
    return false;
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
bool Control::ifAllPass()
{
    for(auto player : players)
    {
        if (player.getPass() == true)
        {
            return false;
        }
    }
    return true;
}
bool Control::winEachWar()
{
    int winnerIndex;
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
            winnerIndex = j;
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
std::vector<Player> Control::getPlayers()
{
    return players;
}
std::vector<int> Control::findIndexVirago()
{
    std::vector<int> indices;
    int max = findMaxVirago();
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].numberOfVirago() == max)
        {
            indices.push_back(i);
        }
    }
    return indices;
}
Player &Control::getDeterminer()
{
    return DeterminerOfWar;
}
Player &Control::youngestPlayer()
{
    std::vector<int> playersAge;
    std::vector<int> youngestIndices;
    for (int i = 0; i < getPlayerNumber(); i++)
    {
        playersAge.push_back(players[i].getAge());
    }
    int minAge = *min_element(playersAge.begin(), playersAge.end()); // Find the minimum age
    for (int i = 0; i < playersAge.size(); i++)
    {
        if (playersAge[i] == minAge)
        {
            youngestIndices.push_back(i);
        }
    }
    srand(time(0));
    int randomIndex = youngestIndices[rand() % youngestIndices.size()];
    return players[randomIndex];
}
Player & Control::getDeterminerPeace()
{
    return DeterminerOfPeace;
}
void Control::findLastDean()
{
    Player player;
    for( auto tempPlayer : players)
    {
        if ( tempPlayer.hasDean() )
        {
           player = tempPlayer;
        }
    }
    setDeterminerPeace(player);
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
std::string Control::getWarPlace()
{
    return warPlace;
}
std::string Control::getPeacePlace()
{
    return peacePlace;
}
std::string Control::findClosestMatch(const std::string &input, const std::vector<std::string> &cards, int threshold)
{
    std::string closestMatch;
    int minDistance = INT_MAX;
    for (const auto &card : cards)
    {
        int distance = levenshteinDistance(input, card);
        if (distance < minDistance)
        {
            minDistance = distance;
            closestMatch = card;
        }
    }
    if (minDistance <= threshold)
    {
        return closestMatch;
    }
    else
    {
        return "";
    }
}
std::string Control::getSeason()
{
    return season;
}
void Control::setIsLeader(bool isLeader)
{
    this->isLeader = isLeader;
}
bool Control::getIsLeader()
{
    return isLeader;
}
void Control::removeGameSaving(int index )
{
    if ( index < files.size() )
    {
        std::remove(files[index].c_str()); // remove file from system
        files.erase(files.begin() + index); // remove filename from vector
    }
}
void Control::addGameName ( const std::string & fileName )
{
   files.push_back(fileName);
}
void Control::saveGame()
{
    std::ofstream outputData;

    outputData.open("../src/saveGame.txt");
    if (!outputData.is_open())
    {
        std::cerr << " Can Not Open File... \n";         
    }

    outputData << playerNumber << "\n";

    for (int i = 0; i < getPlayerNumber(); i++)
    {
        outputData << players[i];
    }

    outputData << provinces.size() << std::endl;
    for (const auto & province : provinces)
    {
        outputData << province << " ";
    }
    outputData << '\n' ;

    outputData << cards.size() << std::endl;
    for (const auto & card : cards)
    {
        outputData << *card << " ";
    }
    outputData << '\n' ;

    outputData << allBurnedCards.size() << std::endl;
    for (const auto & card : allBurnedCards)
    {
        outputData << *card << " ";
    }
    outputData << '\n' ;

    for ( int i = 0 ; i < getPlayerNumber() ; i++ )
    {
        outputData << move[i] << " ";
    }

    outputData << warPlace << std::endl;
    outputData << peacePlace << std::endl;
    outputData << season << std::endl;
    outputData << winner << std::endl;
    outputData << DeterminerOfPeace << std::endl;
    outputData << DeterminerOfWar << std::endl;

    outputData.close(); 
}
void Control::loadGame()
{
    std::ifstream inputData;

    inputData.open("../src/saveGame.txt");
    if (!inputData.is_open())
    {
        std::cerr << " Can Not Open File... \n";         
    }

    int numberOfPlayer, size;
    
    std::string place, season;

    Player tempPlayer;

    std::vector <std::string > provinces;
    std::vector <std::string > move;

    std::vector<std::shared_ptr<Card>> cards; 

    inputData >> numberOfPlayer;
    setPlayerNumber(numberOfPlayer);

    inputData >> size;
    for (int i = 0; i < size; i++)
    {
        inputData >> provinces[i];
        this->provinces[i] = provinces[i]; 
    }
    inputData >> size;
    for (int i = 0; i < size; i++)
    {
        inputData >> cards[i];
        this->cards[i] = cards[i]; 
    }
    inputData >> size;
    for (int i = 0; i < size; i++)
    {
        inputData >> cards[i];
        this->allBurnedCards[i] = cards[i]; 
    }
    for (int i = 0; i < getPlayerNumber(); i++)
    {
         inputData >> move[i];
         this->move[i] = move[i];
    }
    inputData >> place;
    setWarPlace(place);

    inputData >> place;
    setPeace(place);

    inputData >> season;
    setSeason(season);

    inputData >> tempPlayer;
    winner = tempPlayer;

    inputData >> tempPlayer;
    setDeterminer(tempPlayer);

     inputData >> tempPlayer;
    setDeterminerPeace(tempPlayer);
      
}