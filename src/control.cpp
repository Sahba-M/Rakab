
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
#include <string.h>

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
#include "horse.h"

int Control::currentIndex;

Control::Control()
{
    provinceNumber = 15;
    Color color = {186, 186, 186, 120};
    // signColors.resize(15 , color);

    signs =
        {
            {{234, 226}, color, "ELINIA"},
            {{344, 111}, color, "ROLLO"},
            {{455, 203}, color, "TALMONE"},
            {{529, 280}, color, "MORINA"},
            {{609, 219}, color, "BORGE"},
            {{608, 173}, color, "PLADACI"},
            {{698, 161}, color, "BELLA"},
            {{800, 225}, color, "CALINE"},
            {{706, 305}, color, "LIA"},
            {{714, 433}, color, "ATELA"},
            {{635, 521}, color, "PARMA"},
            {{657, 380}, color, "DIMASE"},
            {{527, 387}, color, "OLIVADI"},
            {{492, 504}, color, "ENNA"},
            {{502, 422}, color, "ARMENTO"}};

    int threshold = 3;
}

void Control::setPlayerNumber(int playerNumber)
{
    this->playerNumber = playerNumber;
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

void Control::getInformation()
{
    int age;
    char *name;
    static int index = 0 ;

    if (next)
    {
        Color color = colors[index];
        name = inputName.GetInput();
        age = atoi(inputAge.GetInput());

        std::cout << " before making player " << '\n';
        players.push_back(Player(age, name, color)); // Fill vector of players
        std::cout << " after making player " << '\n';
        inputName.setInputDefault();
        inputAge.setInputDefault();
        next = false;

        for (auto player : players)
        {
            std::cout << player.getName() << "--" << player.getAge() << "/" << "\n" << getCurrentIndex();
        }
        index++;
    }

    if (players.size() == getPlayerNumber())
    {
        setDeterminer(youngestPlayer());
    }
   
}
void Control::distributeCards()
{

    for (Player &player : players)
    {

        for (int i = 0; i < player.numCardsOfPlayer(); i++)
        {
            if (!cards.empty())
            {
                player.addCard(cards.back()); // Gives the last vector card to the player
                cards.pop_back();
            }
        }
    }
}
// void Control::readProvinces()
// {
//     std::string province, ignore;
//     std::ifstream inputProvinces;
//     setProvinceNumber(provinceNumber);

//     inputProvinces.open("../src/map.txt");
//     if (!inputProvinces.is_open())
//     {
//         std::cerr << " Can Not Open File... " << std::endl;
//     }
//     for (int i = 0; i < getProvinceNumber(); i++)
//     {
//         inputProvinces >> ignore;
//         inputProvinces >> province;
//         provinces.push_back(province);
//     }
//     inputProvinces.close();
// }
// void Control::showUncaptured()
// {
//     for (int i = 0; i < provinces.size(); i++)
//     {
//         std::cout << provinces[i] << "  ";
//     }
// }
void Control::setWar()
{
    LeaderCard leader;
    HorserCard horse;

    if (getIfDean())
    {
        selectPeacePlace(getDeterminerPeace());
        setIfDean(false);
    }
    // selectWarPlace(getDeterminer());

    int startIndex = findPlayerIndex(getDeterminer());
    // int currentIndex = startIndex;
    setCurrentIndex(startIndex);

    system("cls");

    while (!endEachWar())
    {
        for (int i = 0; i < getPlayerNumber(); i++)
        {
            // showAllCaptured();
            // showPlayGround();
            // std::cout << "\n The War Is Over => " << getWarPlace() << "\n\n ";
            selectMove(players[getCurrentIndex()], currentIndex);
            if (players[getCurrentIndex()].getIfLeader())
            {
                
                leader.useCard(players, -1);
                setIsLeader(true);
                system("cls");
                break;
            }
            else if (players[getCurrentIndex()].getIfHorse())
            {
                horse.useCard(players, -1);
                // setIsHorse(true);
                system("cls");
                break;
            }
            // currentIndex = (currentIndex + 1) % players.size();
            setCurrentIndex((getCurrentIndex() + 1) % players.size());

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
                // guideGame();
                choice = getch();
                system("cls");
                // showAllCaptured();
                // showPlayGround();
                selectMove(player, index);
            }
            else if (selection == 2)
            {
                // guideCards();
                choice = getch();
                system("cls");
                // showAllCaptured();
                // showPlayGround();
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
// void Control::showPlayGround()
// {
//     std::cout << "--------------------------- \n";
//     for (int i = 0; i < players.size(); i++)
//     {
//         players[i].showUsedCards();
//     }
//     std::cout << "--------------------------- \n";
// }
void Control::selectWarPlace()
{

    Vector2 mousePosition = GetMousePosition();

    const Color GRAY_COLOR = {186, 186, 186, 120};

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        for (int i = 0; i < getProvinceNumber(); i++) // Repeat for each province
        {
            float distance = sqrtf(powf(mousePosition.x - signs[i].position.x, 2) + powf(mousePosition.y - signs[i].position.y, 2));
            // Calculate the distance between the mouse position and the current marker position
            if (distance <= 11 && !isBlackCircle())
            { // Is the mouse in the circle or not?
                if (CompareColors(signs[i].color, GRAY_COLOR))
                {
                    setWarPlace(signs[i].name);
                    signs[i].color = BLACK;
                    provinceIndex = i ;
                    BeginDrawing();
                    drawSigns();
                    EndDrawing();
                    sleep(2);
                    currentScreen = DEAL;

                    break;
                }
            }
        }
    }
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

    // for (int i = 0; i < getPlayerNumber(); i++)
    // {
    //     if (players[i].hasDean())
    //     {
    //         dean.useCard(players, i);
    //         setIfDean(true);
    //     }
    // }
    if (season == "winter")
    {
        winter.useCard(players, -1);
    }
    for (int i = 0; i < getPlayerNumber(); i++)
    {
        if (players[i].hasDrummer())
        {
            double calcuteNumber = pow(1.5, players[i].numberOfDrummer());
            drummer.useCard(players, i, calcuteNumber);
        }
    }
    
    if (season == "spring")
    {
        spring.useCard(players, -1);
    }
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
    // for (int i = 0; i < getPlayerNumber(); i++)
    // {
    //     if (players[i].hasVirago())
    //     {
    //         for (int j = 0; j < players[i].numberOfVirago(); j++)
    //         {
    //             virago.useCard(players, i);
    //         }
    //     }
    // }
    // findLastDean();
    // setSeason("temp");
    for (auto player : players)
    {
        // std::cout << "pass" << std::boolalpha << player.getPass();
        std::cout << player.getScorePlayer() << "\n";
    }
}
void Control::setSeason(std::string season)
{
    this->season = season;
}
void Control::setPlayersReady()
{
    for (auto & player : players)
    {
        player.setPass(false);
    }
    std::cout << "test ready";
}
void Control::run()
{
    // Map map;
    // map.readMatrix();
    // map.readUnorderedMap();
    // setCards();
    // shuffleCards();
    // controlNumber();
    // getInformation();
    // distributeCards();
    // readProvinces();
    // setDeterminer(youngestPlayer());
    // while (!endGame())
    // {
    //     setPlayersReady();
    //     setWar();
    //     askBurn();
    //     burnCards();
    //     chargeCards();
    // }

    startGame();
}
void Control::burnCards()
{
    for (auto & player : players)
    {
        std::cout << "test burn" << std::endl;
        player.burnCardsPlayer();
        player.insertBurnedCard(allBurnedCards); // for all player
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
            player.insertHandCard(allBurnedCards);
            // allBurnedCards.insert(allBurnedCards.end(), player.getHandCards().begin(), player.getHandCards().end());
        }
        cards.insert(cards.end(), allBurnedCards.begin(), allBurnedCards.end());
        shuffleCards();
        distributeCards();
        std::cout << "test charge" << std::endl;
    }
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
void Control::setIfDean(bool ifDean)
{
    this->ifDean = ifDean;
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

        for (auto &player : players)
        {
            player.setPass(false);
            player.setIfLeader(false);
        }
        return true;
    }
    return false;
}
void Control::updateHorsePlayers()
{
    for (auto &player : players)
    {
        player.setIfHorse(false);
    }
}
int Control::getPlayerNumber()
{
    return playerNumber;
}
int Control::findPlayerIndex(Player &player)
{
    std::string playerName , temp ;
    playerName = player.getName();
    for (int i = 0; i < players.size(); i++)
    {
        temp = players[i].getName();
        // std::cout << players[i].getName() << "--" << player.getName() << std::endl;
        if (playerName == temp)
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
    for (auto player : players)
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

    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].hasHorse())
        {
            winnerIndex = i;
            winner = players[i];
            players[i].addProvinces(warPlace);
            updateHorsePlayers();
            return true;
        }
    }
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
Player &Control::getDeterminerPeace()
{
    return DeterminerOfPeace;
}
void Control::findLastDean()
{
    Player player;
    for (auto tempPlayer : players)
    {
        if (tempPlayer.hasDean())
        {
            player = tempPlayer;
        }
    }
    setDeterminerPeace(player);
}
std::string Control::getWarPlace() const
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
void Control::setIsHorse(bool isHorse)
{
    this->isHorse = isHorse;
}
bool Control::getIsHorse()
{
    return isHorse;
}
void Control::removeGameSaving(int index)
{
    if (index < files.size())
    {
        std::remove(files[index].c_str());  // remove file from system
        files.erase(files.begin() + index); // remove filename from vector
    }
}
void Control::addGameName(const std::string &fileName)
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
    for (const auto &province : provinces)
    {
        outputData << province << " ";
    }
    outputData << '\n';

    outputData << cards.size() << std::endl;
    for (const auto &card : cards)
    {
        outputData << *card << " ";
    }
    outputData << '\n';

    outputData << allBurnedCards.size() << std::endl;
    for (const auto &card : allBurnedCards)
    {
        outputData << *card << " ";
    }
    outputData << '\n';

    for (int i = 0; i < getPlayerNumber(); i++)
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

    std::vector<std::string> provinces;
    std::vector<std::string> move;

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

// -- graphic functions --

void Control::startGame()
{
    currentScreen = MENU;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Update();
        BeginDrawing();
        Draw();
        DrawMousePosition();
        EndDrawing();
    }

    CloseWindow();
}
int Control::getCurrentScreen()
{
    return currentScreen;
}
void Control::Draw()
{
    switch (currentScreen)
    {
    case MENU:
        setMenuBackground();
        setTitle();
        setMenuList();
        break;
    case NUMBER:
        setAskBackground();
        askNumber();
        break;
    case INFO:
        setAskBackground();
        drawInput();
        break;
    case MAP:
        drawSigns();
        break;
    case DEAL:

        break;
    case GAME:
        if (!endEachWar())
        {
            setGameBackground();
            drawCards();
            managePassButton();
        }
        else
        {
            cardAction();
            currentScreen = WINNER;
        }
        break;
    case WINNER:
        determineWinner();
        break;
    }
}
void Control::Update()
{
    switch (currentScreen)
    {
    case INFO:
        updateInput();
        getInformation();
        break;
    case MAP:
        askMap();
        changeCircleColor();
        break;
    case DEAL:
       
        deal();
    case GAME:
        updateCards();

        break;
    }
}
void Control::setMenuBackground()
{
    DrawTexture(myAsset.menu, 0, 0, WHITE);
}
void Control::setAskBackground()
{
    DrawTexture(myAsset.info, 0, 0, WHITE); // Draw the image

    TextButton goBack;
    goBack.bounds = {30, 30, 150, 60};
    goBack.text = "Back To MENU";

    Vector2 mousePosition = GetMousePosition(); // Save the current mouse coordinates

    if (CheckCollisionPointRec(mousePosition, goBack.bounds))
    {
        goBack.color = BLACK;
        goBack.buttonColor = {174, 185, 191, 200};

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentScreen = MENU;
        }
    }
    else
    {
        goBack.color = {234, 237, 240, 255};       // Change text color
        goBack.buttonColor = {101, 107, 110, 200}; // Change button color
    }

    DrawRectangleRounded(goBack.bounds, 0.4f, 0, goBack.buttonColor);
    DrawTextEx(myAsset.listFont, goBack.text, {goBack.bounds.x + 12, goBack.bounds.y + 20}, 25, 2, goBack.color);
}
void Control::setTitle()
{
    Color textColor = {4, 9, 72, 255};
    const char *text = "Rakab";

    DrawTextEx(myAsset.title, text, (Vector2){430, 50}, 90, 2, textColor);
}
void Control::setMenuList()
{
    buttons.reserve(4);

    buttons[0].text = "New Game";
    buttons[0].bounds = {450, 230, 250, 45};

    buttons[1].text = "Load Game";
    buttons[1].bounds = {450, 280, 250, 45};

    buttons[2].text = "Help";
    buttons[2].bounds = {450, 330, 250, 45};

    buttons[3].text = "Exit";
    buttons[3].bounds = {450, 380, 250, 45};

    Vector2 mousePosition = GetMousePosition();

    for (int i = 0; i < 4; i++)
    {
        if (CheckCollisionPointRec(mousePosition, buttons[i].bounds))
        {
            // Change colors on button click
            buttons[i].buttonColor = {0, 0, 0, 110}; // button color
            buttons[i].color = {234, 237, 240, 255}; // text color
        }
        else
        {
            buttons[i].color = BLACK;
            buttons[i].buttonColor = {0, 0, 0, 30};
        }
    }

    // Draw button background
    // Draw button text
    DrawRectangle(buttons[0].bounds.x, buttons[0].bounds.y, buttons[0].bounds.width, buttons[0].bounds.height, buttons[0].buttonColor);
    DrawTextEx(myAsset.listFont, buttons[0].text, {buttons[0].bounds.x + 70, buttons[0].bounds.y + 10}, 30, 2, buttons[0].color);

    DrawRectangle(buttons[1].bounds.x, buttons[1].bounds.y, buttons[1].bounds.width, buttons[1].bounds.height, buttons[1].buttonColor);
    DrawTextEx(myAsset.listFont, buttons[1].text, {buttons[1].bounds.x + 67, buttons[1].bounds.y + 10}, 30, 2, buttons[1].color);

    DrawRectangle(buttons[2].bounds.x, buttons[2].bounds.y, buttons[2].bounds.width, buttons[2].bounds.height, buttons[2].buttonColor);
    DrawTextEx(myAsset.listFont, buttons[2].text, {buttons[2].bounds.width / 2 + buttons[2].bounds.x - 25, buttons[2].bounds.y + 10}, 30, 2, buttons[2].color);

    DrawRectangle(buttons[3].bounds.x, buttons[3].bounds.y, buttons[3].bounds.width, buttons[3].bounds.height, buttons[3].buttonColor);
    DrawTextEx(myAsset.listFont, buttons[3].text, {buttons[3].bounds.width / 2 + buttons[3].bounds.x - 25, buttons[3].bounds.y + 10}, 30, 2, buttons[3].color);

    startButton();
    helpButton();
    exitButton();
}
void Control::helpButton()
{
    Vector2 mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition, buttons[2].bounds))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            system("start C:/assets/help.pdf");
        }
    }
}
void Control::exitButton()
{
    Vector2 mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition, buttons[3].bounds))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            CloseWindow();
        }
    }
}
void Control::startButton()
{
    Vector2 mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition, buttons[0].bounds))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentScreen = NUMBER;
        }
    }
}
void Control::askNumber()
{
    // ClearBackground(RAYWHITE);
    Color recColor = {170, 170, 170, 170}; // Background color
    float roundness = 0.3f;
    Rectangle temp = {325, 90, 450, 70};

    DrawRectangleRounded(temp, 0.3f, 0, recColor);
    DrawTextEx(myAsset.askFont, "Choose The Number Of Players :", {340, 110}, 35, 2, BLACK);

    numButtons.reserve(4);

    numButtons[0].text = "3";
    numButtons[0].bounds = {430, 200, 100, 60};

    numButtons[1].text = "4";
    numButtons[1].bounds = {550, 200, 100, 60};

    numButtons[2].text = "5";
    numButtons[2].bounds = {430, 280, 100, 60};

    numButtons[3].text = "6";
    numButtons[3].bounds = {550, 280, 100, 60};

    Vector2 mousePosition = GetMousePosition();

    for (int i = 0; i < 4; i++)
    {
        if (CheckCollisionPointRec(mousePosition, numButtons[i].bounds))
        {
            // Change colors on button click
            numButtons[i].buttonColor = {191, 155, 129, 230};
            numButtons[i].color = {234, 237, 240, 255};
        }
        else
        {
            numButtons[i].buttonColor = {141, 108, 88, 170};
            numButtons[i].color = BLACK;
        }
    }

    for (int i = 0; i < 4; i++) // Draw text and buttons
    {
        DrawRectangleRounded(numButtons[i].bounds, roundness, 0, numButtons[i].buttonColor);
        DrawTextEx(myAsset.askFont, numButtons[i].text, {numButtons[i].bounds.x + 40, numButtons[i].bounds.y + 10}, 30, 2, numButtons[i].color);
    }

    for (int i = 0; i < 4; i++)
    {
        if (CheckCollisionPointRec(mousePosition, numButtons[i].bounds))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                setPlayerNumber(i + 3); // Set the number of players
                currentScreen = INFO;   // Change the screen to the information screen
                break;
            }
        }
    }
}
void Control::drawInput()
{
    static int counter = 1; // Player number

    if (counter <= getPlayerNumber())
    {
        Color backColor = {108, 194, 237, 200};

        char text[2];
        text[0] = counter + '0'; // player number (Convert character to number)
        text[1] = '\0';          // end

        Rectangle back = {500, 70, 150, 70};
        DrawRectangleRounded(back, 0.4f, 0, backColor);
        DrawRectangleRoundedLines(back, 0.4f, 0, 3, {6, 87, 128, 255});
        DrawTextEx(myAsset.inputFont, "Player", {525, 90}, 25, 2, {28, 52, 40, 255});
        DrawTextEx(myAsset.inputFont, text, {615, 90}, 25, 2, {28, 52, 40, 255});

        inputName.DrawName();

        inputAge.DrawAge();

        submit.bounds = {500, 420, 150, 70};
        submit.text = "NEXT";

        Vector2 mousePosition = GetMousePosition();

        if (CheckCollisionPointRec(mousePosition, submit.bounds))
        {
            submit.color = WHITE;
            submit.buttonColor = {137, 162, 97, 180};
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (!inputAge.isEmpty() && !inputName.isEmpty())
                {
                    counter++;
                    next = true;
                }
            }
        }
        else
        {
            submit.color = {28, 52, 40, 255};
            submit.buttonColor = {188, 206, 170, 180};
        }
        DrawRectangleRounded(submit.bounds, 0.4f, 0, submit.buttonColor); // draw next button
        DrawTextEx(myAsset.inputFont, submit.text, {submit.bounds.x + 45, submit.bounds.y + 20}, 25, 2, submit.color);
    }
    else
        currentScreen = MAP; // Transfer to the game screen
}
void Control::updateInput()
{
    inputName.Update();
    inputAge.Update();
}
void Control::askMap()
{
    const char *playerName = getDeterminer().getName();

    DrawTexture(myAsset.game, 0, 0, WHITE);                            // background image
    DrawTextureEx(myAsset.map, (Vector2){200, 75}, 0.0f, 0.5f, WHITE); // Map image

    DrawTextEx(myAsset.askFont, playerName, {500, 15}, 30, 2, BLACK); // Print the name of the player
    DrawTextEx(myAsset.askFont, " Choose The War Place!", {380, 35}, 30, 2, BLACK);
    DrawTextEx(myAsset.askFont, " Click On The Sign To Select  ", {380, 580}, 30, 2, BLACK);
    // selectWarPlace(players[0]);
    selectWarPlace();
}
void Control::drawSigns()
{
    for (int i = 0; i < getProvinceNumber(); i++)
    {
        DrawCircle(signs[i].position.x, signs[i].position.y, 11, signs[i].color);
    }
}

void Control::setGameBackground()
{
    DrawTexture(myAsset.table, 0, 0, WHITE);

    char place[20] ;
    std::string temp = getWarPlace();
    strcpy(place, temp.c_str());
    DrawTextEx(myAsset.askFont , place , {490,30} , 30 , 2 , BLACK);

    TextButton help;
    help.bounds = {7, 13, 60, 60};
    help.text = "?";

    Vector2 position = {239, 607};
    if (players.size() > 0 && players[0].getName() && strlen(players[0].getName()) > 0)
    {
        // Draw bold effect for player 0
        DrawTextEx(myAsset.name, players[0].getName(), {position.x - 1, position.y}, 30, 2, BLACK); // Draw shadow
        DrawTextEx(myAsset.name, players[0].getName(), {position.x + 1, position.y}, 30, 2, BLACK); // Draw shadow
        DrawTextEx(myAsset.name, players[0].getName(), {position.x, position.y - 1}, 30, 2, BLACK); // Draw shadow
        DrawTextEx(myAsset.name, players[0].getName(), {position.x, position.y + 1}, 30, 2, BLACK); // Draw shadow
        // Draw the text in the original position
        DrawTextEx(myAsset.name, players[0].getName(), position, 30, 2, WHITE); // Draw main text
    }

    position = {770, 607};
    if (players.size() > 1 && players[1].getName() && strlen(players[1].getName()) > 0)
    {
        // Draw bold effect for player 1
        DrawTextEx(myAsset.name, players[1].getName(), {position.x - 1, position.y}, 30, 2, BLACK);
        DrawTextEx(myAsset.name, players[1].getName(), {position.x + 1, position.y}, 30, 2, BLACK);
        DrawTextEx(myAsset.name, players[1].getName(), {position.x, position.y - 1}, 30, 2, BLACK);
        DrawTextEx(myAsset.name, players[1].getName(), {position.x, position.y + 1}, 30, 2, BLACK);
        DrawTextEx(myAsset.name, players[1].getName(), position, 30, 2, WHITE);
    }

    position = {1045, 330};
    Vector2 origin = {0, 0};
    float rotation = -90.0f;
    if (players.size() > 2 && players[2].getName() && strlen(players[2].getName()) > 0)
    {
        // Draw bold effect for player 2
        DrawTextPro(myAsset.name, players[2].getName(), {position.x - 1, position.y}, origin, rotation, 30, 2, BLACK);
        DrawTextPro(myAsset.name, players[2].getName(), {position.x + 1, position.y}, origin, rotation, 30, 2, BLACK);
        DrawTextPro(myAsset.name, players[2].getName(), {position.x, position.y - 1}, origin, rotation, 30, 2, BLACK);
        DrawTextPro(myAsset.name, players[2].getName(), {position.x, position.y + 1}, origin, rotation, 30, 2, BLACK);
        DrawTextPro(myAsset.name, players[2].getName(), position, origin, rotation, 30, 2, WHITE);
    }

    if (players.size() > 3)
    {
        const char *playerName3 = players[3].getName();
        if (playerName3 && strlen(playerName3) > 0)
        {
            position = {810, 29};
            origin = {0, 0};
            rotation = -180.0f;
            DrawTextPro(myAsset.name, playerName3, {position.x - 1, position.y}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName3, {position.x + 1, position.y}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName3, {position.x, position.y - 1}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName3, {position.x, position.y + 1}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName3, position, origin, rotation, 30, 2, WHITE);
        }
    }

    if (players.size() > 4)
    {
        const char *playerName4 = players[4].getName();
        if (playerName4 && strlen(playerName4) > 0)
        {
            position = {280, 31};
            origin = {0, 0};
            rotation = -180.0f;
            DrawTextPro(myAsset.name, playerName4, {position.x - 1, position.y}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName4, {position.x + 1, position.y}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName4, {position.x, position.y - 1}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName4, {position.x, position.y + 1}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName4, position, origin, rotation, 30, 2, WHITE);
        }
    }

    if (players.size() > 5)
    {
        const char *playerName5 = players[5].getName();
        if (playerName5 && strlen(playerName5) > 0)
        {
            position = {30, 280};
            origin = {0, 0};
            rotation = 90.0f;
            DrawTextPro(myAsset.name, playerName5, {position.x - 1, position.y}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName5, {position.x + 1, position.y}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName5, {position.x, position.y - 1}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName5, {position.x, position.y + 1}, origin, rotation, 30, 2, BLACK);
            DrawTextPro(myAsset.name, playerName5, position, origin, rotation, 30, 2, WHITE);
        }
    }

    Vector2 mousePosition = GetMousePosition(); // Save the current mouse coordinates

    if (CheckCollisionPointRec(mousePosition, help.bounds))
    {
        help.color = WHITE;
        help.buttonColor = {31, 102, 110, 200};

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            system("start C:/assets/help.pdf");
        }
    }
    else
    {
        help.color = BLACK;                      // Change text color
        help.buttonColor = {95, 175, 184, 200}; // Change button color
    }

    DrawRectangleRounded(help.bounds, 0.4f, 0, help.buttonColor);
    DrawTextEx(myAsset.listFont, help.text, {help.bounds.x + 22, help.bounds.y + 18}, 35, 2, help.color);
}

bool Control::isBlackCircle()
{
    for (int i = 0; i < getProvinceNumber(); i++)
    {
        if (CompareColors(signs[i].color, BLACK))
        {
            return true;
        }
    }
    return false;
}
bool Control::CompareColors(Color a, Color b)
{
    return (a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a);
}

void Control::changeCircleColor()
{
    Vector2 mousePosition = GetMousePosition();

    for (int i = 0; i < getProvinceNumber(); i++)
    {
        float distance = sqrtf(powf(mousePosition.x - signs[i].position.x, 2) + powf(mousePosition.y - signs[i].position.y, 2));

        if (distance <= 11 && CompareColors(signs[i].color, BLACK))
        {
            // for (Player& player : players)
            // {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                signs[i].color = RED;
                BeginDrawing();
                drawSigns();
                EndDrawing();
                sleep(2);
                currentScreen = GAME;
                break;
            }
            // }
            break;
        }
    }
}

void Control::DrawMousePosition()
{
    // دریافت موقعیت موس
    Vector2 mousePosition = GetMousePosition();

    // تبدیل موقعیت موس به رشته
    char positionText[64];
    sprintf(positionText, "Mouse X: %d, Y: %d", (int)mousePosition.x, (int)mousePosition.y);

    // رسم موقعیت موس در گوشه بالای صفحه
    DrawText(positionText, 10, 10, 20, BLACK);
}

void Control::drawCards()
{
    int index = getCurrentIndex();
    Vector2 origin = {0, 0};
    LeaderCard leader;
    bool end = false ;

    players[0].drawUseCards(200, 445, myAsset, origin, 0);
    players[1].drawUseCards(559, 445, myAsset, origin, 0);
    players[2].drawUseCardSpecialPlayer(885, 220, myAsset, origin, -90);
    if (players.size() > 3)
        players[3].drawUseCards(630, 200, myAsset, origin, -180);
    if (players.size() > 4)
        players[4].drawUseCards(270, 200, myAsset, origin, -180);
    if (players.size() > 5)
        players[5].drawUseCardSpecialPlayer(187, 165, myAsset, origin, 90);

    // std::cout << "test index : " << index << "    ";

    // for (int i = 0; i < getPlayerNumber(); i++)
    // {
        if (getCurrentIndex() == 0)
        {
            if (!players[0].getPass() && end == false)
            {
                
                players[0].drawCards(115, 500, myAsset, origin, 0);
                if (players[0].getSeason() == "winter")
                {
                    setSeason(players[0].getSeason());
                }
                else if (players[0].getSeason() == "spring")
                {
                    setSeason(players[0].getSeason());
                } 
            }
        }
        else
            players[0].drawBackCards(115, 500, myAsset, origin, 0);

        if (getCurrentIndex() == 1)
        {
            if (!players[1].getPass() && end == false)
            {
                players[1].drawCards(645, 500, myAsset, origin, 0);
                if (players[1].getSeason() == "winter")
                {
                    setSeason(players[1].getSeason());
                }
                else if (players[1].getSeason() == "spring")
                {
                    setSeason(players[1].getSeason());
                }
                
            }
        }
        else
            players[1].drawBackCards(645, 500, myAsset, origin, 0);

        if (getCurrentIndex() == 2)
        {
            if (!players[2].getPass() && end == false)
            {
                players[2].drawCardSpecialPlayer(937, 227, myAsset, origin, -90);
                if (players[2].getSeason() == "winter")
                {
                    setSeason(players[2].getSeason());
                }
                else if (players[2].getSeason() == "spring")
                {
                    setSeason(players[2].getSeason());
                }  
            }
        }
        else
            players[2].drawBackCardSpecialPlayer(937, 227, myAsset, origin, -90);

        if (players.size() > 3)
        {
            if (getCurrentIndex() == 3)
            {
                if (!players[3].getPass() && end == false)
                {
                    players[3].drawCards(730, 139, myAsset, origin, -180);
                    if (players[3].getSeason() == "winter")
                    {
                        setSeason(players[3].getSeason());
                    }
                    else if (players[3].getSeason() == "spring")
                    {
                        setSeason(players[3].getSeason());
                    }    
                }
            }
            else
                players[3].drawBackCards(730, 139, myAsset, origin, -180);
        }

        if (players.size() > 4)
        {
            if (getCurrentIndex() == 4)
            {
                if (!players[4].getPass() && end == false)
                {
                    players[4].drawCards(195, 139, myAsset, origin, -180);
                    if (players[4].getSeason() == "winter")
                    {
                        setSeason(players[4].getSeason());
                    }
                    else if (players[4].getSeason() == "spring")
                    {
                        setSeason(players[4].getSeason());
                    }  
                }
            }
            else
                players[4].drawBackCards(195, 139, myAsset, origin, -180);
        }

        if (players.size() > 5)
        {
            if (getCurrentIndex() == 5)
            {
                if (!players[5].getPass() && end == false)
                {
                    players[5].drawCardSpecialPlayer(140, 165, myAsset, origin, 90);
                    if (players[5].getSeason() == "winter")
                    {
                        setSeason(players[5].getSeason());
                    }
                    else if (players[5].getSeason() == "spring")
                    {
                        setSeason(players[5].getSeason());
                    }
                }
            }
            else
                players[5].drawBackCardSpecialPlayer(140, 165, myAsset, origin, 90);
        }
}
void Control::updateCards()
{
    Vector2 origin = {0, 0};
    LeaderCard leader;
    HorserCard horse;
    switch (getCurrentIndex())
    {
    case 0:
        if (!players[0].getPass())
        {
            players[0].updateCardsDown(115, 500, 70, 108, cardselected);
            playerCard.push_back(players[0]);

            if (players[0].getIfLeader())
            {
                leader.useCard(players, 0);
                setIsLeader(true);
            }
            else if (players[0].getIfHorse())
            {
                horse.useCard(players, 0);
                setIsHorse(true);
            }
        }
        else
            setCurrentIndex((getCurrentIndex() + 1) % players.size());
        break;

    case 1:
        if (!players[1].getPass())
        {
            players[1].updateCardsDown(645, 500,70, 108, cardselected);
            playerCard.push_back(players[1]);

            if (players[1].getIfLeader())
            {
                leader.useCard(players, 0);
                setIsLeader(true);
            }
            else if (players[1].getIfHorse())
            {
                horse.useCard(players, 0);
                setIsHorse(true);
            }
        }
        else
            setCurrentIndex((getCurrentIndex() + 1) % players.size());
        break;

    case 2:
        if (!players[2].getPass())
        {
            players[2].updateCardsSpecialR(937, 227, 70, 108, cardselected);
            playerCard.push_back(players[2]);
   
            if (players[2].getIfLeader())
            {
                leader.useCard(players, 0);
                setIsLeader(true);
            }
            else if (players[2].getIfHorse())
            {
                horse.useCard(players, 0);
                setIsHorse(true);
            }
        }
        else
            setCurrentIndex((getCurrentIndex() + 1) % players.size());
        break;

    case 3:
        if (players.size() > 3)
        {
            if (!players[3].getPass())
            {
                players[3].updateCardsTop(730, 139,  70, 108, cardselected);
                playerCard.push_back(players[3]);

                if (players[3].getIfLeader())
                {
                    leader.useCard(players, 0);
                    setIsLeader(true);
                }
                else if (players[3].getIfHorse())
            {
                horse.useCard(players, 0);
                setIsHorse(true);
            }
            }  
            else
                setCurrentIndex((getCurrentIndex() + 1) % players.size());
        }
        break;

    case 4:
        if (players.size() > 4)
        {
            if (!players[4].getPass())
            {
                players[4].updateCardsTop(195, 139,  70, 108, cardselected);
                playerCard.push_back(players[4]);

                if (players[4].getIfLeader())
                {
                    leader.useCard(players, 0);
                    setIsLeader(true);
                }
                else if (players[4].getIfHorse())
            {
                horse.useCard(players, 0);
                setIsHorse(true);
            }
            }
            else
                setCurrentIndex((getCurrentIndex() + 1) % players.size());
        }
        break;

    case 5:
        if (players.size() > 5)
        {
            if (!players[5].getPass())
            {
                players[5].updateCardsSpecialL(140, 165,  108, 70, cardselected);
                playerCard.push_back(players[5]);

                if (players[5].getIfLeader())
                {
                    leader.useCard(players, 0);
                    setIsLeader(true);
                }
                else if (players[5].getIfHorse())
            {
                horse.useCard(players, 0);
                setIsHorse(true);
            }
            }
            else
                setCurrentIndex((getCurrentIndex() + 1) % players.size());
        }
        break;
    }

    if (cardselected)
    {
        setCurrentIndex((getCurrentIndex() + 1) % players.size());
        std::cout << "test index : " << getCurrentIndex() << std::endl;
        cardselected = false;
    }
}
void Control::deal()
{
    if ( ifDeal )
    {
        std::cout << "test deal" << std::endl;
        setCards();
        shuffleCards();
        distributeCards();
        ifDeal = false;
    }
    setPlayersReady(); // This function false all passes

    for ( auto player : players )
    std::cout << " test pass " << std::boolalpha << player.getPass() << " - ";

    setCurrentIndex(findPlayerIndex(getDeterminer()));
    std::cout << "current index test : " << getCurrentIndex() << "..." << findPlayerIndex(getDeterminer()) << "\n";
    currentScreen = GAME;
}

int &Control::getCurrentIndex()
{
    return currentIndex;
}
void Control::setCurrentIndex(int currentIndex)
{
    this->currentIndex = currentIndex;
}
void Control::managePassButton()
{
    passButton.text = "Pass";
    passButton.bounds = {615, 280, 80, 80};
    DrawRectangleRounded(passButton.bounds, 0.3f, 0, passButton.buttonColor);
    DrawTextEx(myAsset.listFont, passButton.text, {passButton.bounds.x + 15, passButton.bounds.y + 30}, 30, 2, passButton.color);

    Vector2 mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition, passButton.bounds))
    {
        // Change colors on button click
        passButton.buttonColor = {191, 99, 99, 170}; // button color
        passButton.color = {237, 237, 237, 255};     // text color
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            players[getCurrentIndex()].setPass(true);
            setCurrentIndex((getCurrentIndex() + 1) % players.size());
        }
    }
    else
    {
        passButton.buttonColor = {242, 174, 174, 170};
        passButton.color = BLACK;
    }
}

void Control::determineWinner()
{
    // std::cout << " test winner" << std::endl;
    DrawTexture(myAsset.winner, 0, 0, WHITE);
    // std::cout << " test after back" << std::endl;

    if (winEachWar())
    {
        // std::cout << " test if start";
        const char *name = winner.getName();
        DrawTextEx(myAsset.askFont, " Winner : ", {400, 175}, 90, 2, WHITE);
        DrawTextEx(myAsset.askFont, name, {400, 260}, 90, 2, WHITE);
        DrawTextEx(myAsset.askFont, " - CLICK TO SKIP - ", {420, 370}, 25, 2, WHITE);


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
        signs[provinceIndex].color = winner.getColor();
    }
    else
    {
        DrawTextEx(myAsset.askFont, " This War Has No Winners! ", {200, 280}, 70, 2, WHITE);
        DrawTextEx(myAsset.askFont, " - CLICK TO SKIP - ", {455, 375}, 25, 2, WHITE);
        if (!changeDeterminerL())
        {
            if (!changeDeterminer())
            {
                setDeterminer(players[playersIndices.back()]); // set the last player who pass the game
            }
        }
        signs[provinceIndex].color = {186, 186, 186, 120};

    }

    for (int i = 0; i < getPlayerNumber(); i++) // to update move vector from "pass" to "temp"
    {
        players[i].setSeason("temp");
    }
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        burnCards();
        chargeCards();
        currentScreen = MAP;
    }
}
