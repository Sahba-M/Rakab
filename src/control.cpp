
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
#include "horse.h"

Control::Control()
{
    provinceNumber = 15;
    Color color = { 186 , 186 , 186 , 120 };
    // signColors.resize(15 , color);

    signs = {  
    { {234 , 226} , color , "ELINIA" },
    { {344 , 111} , color , "ROLLO"  },
    { {455 , 203} , color , "TALMONE"},
    { {529 , 280} , color , "MORINA" },
    { {609 , 219} , color , "BORGE"  },
    { {608 , 173} , color , "PLADACI"},
    { {698 , 161} , color , "BELLA"  },
    { {800 , 225} , color , "CALINE" },
    { {706 , 305} , color , "LIA"    },
    { {714 , 433} , color , "ATELA"  },
    { {635 , 521} , color , "PARMA"  },
    { {657 , 380} , color , "DIMASE" },
    { {527 , 387} , color , "OLIVADI"},
    { {492 , 504} , color , "ENNA"   },
    { {502 , 422} , color , "ARMENTO"}
    };

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
    char* name;
    std::string color = "test";

     if ( next )
    {
        name = inputName.GetInput();
        age = atoi(inputAge.GetInput());

        players.push_back(Player(age, name, color)); // Fill vector of players
        std::cout << name << "-" << age ;
        inputName.setInputDefault();
        inputAge.setInputDefault();
        next = false ;


        for(auto player : players)
        {
            std::cout << player.getName() << "--" << player.getAge() << "/" ;
        }
    }
    // for (int i = 0; i < getPlayerNumber(); i++)
    // {
        // std::cout << " Player " << i + 1 << " : " << '\n' << " Enter Your Name : ";
                 
        // std::cin.ignore();
        // std::getline(std::cin, name);


        // std::cout << " Enter Your Age : ";
        // std::cin >> age;
        // age = controlAge();

        // color = controlColors();
        // std::cout << "-----------------------\n";
        
        // graphic.transferInformation(name , age);
        // std::cout << name << "---" << age ;
        // std::cin >> color ;
        

    // }
    // system("cls");
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
    HorserCard horse;
    
    
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
                break;
            }
            else if (players[currentIndex].getIfHorse())
            {
                horse.useCard(players,-1);
                //setIsHorse(true);
                system("cls");
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
    // bool found = true;
    // std::string chooseProvince;
    // do
    // {
    //     std::cout << "\n ";
    //     std::cout << "---------------------------------------------------------------------------------------------------------\n ";
    //     for (int i = 0; i < provinces.size(); i++)
    //     {
    //         std::cout << provinces[i] << "  ";
    //     }
    //     std::cout << "\n ---------------------------------------------------------------------------------------------------------\n\n\n ";
    //     std::cout << std::endl;

    //     if (found == true)
    //         std::cout << " " << player.getName() << " Enter Your Chosen Province: ";
    //     std::cin >> chooseProvince;

    //     if ( chooseProvince == getPeacePlace())
    //     {
    //         std::cout << " You Can Not Choose This province ; Because It is Peace Place ." << std::endl;
    //         found = false;
    //     }
    //     else
    //     {
    //         auto elementFound = std::find(provinces.begin(), provinces.end(), chooseProvince);
    //         if (elementFound != provinces.end())
    //         {
    //             found = true;
    //             break;
    //         }
    //         else
    //         {
    //             std::cout << " \n ERROR: Please Enter Your Province Again : " << std::endl;
    //             found = false;
    //         }
    //     }
    // } while (!found);
    Vector2 mousePosition = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
    {
            for (int i = 0; i < getProvinceNumber() ; i++) // Repeat for each province
            {
                float distance = sqrtf(powf(mousePosition.x - signs[i].position.x, 2) + powf(mousePosition.y - signs[i].position.y, 2));
                // Calculate the distance between the mouse position and the current marker position
                if (distance <= 11) { //Is the mouse in the circle or not?
                    setWarPlace(signs[i].name);
                    currentScreen = GAME ;
                    break;  
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
    // Map map;
    // map.readMatrix();
    // map.readUnorderedMap();
    // setCards();
    // shuffleCards();
    // controlNumber();
    // getInformation();
    // distributeCards();
    // readProvinces();
     //setDeterminer(youngestPlayer());
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
void Control::updateHorsePlayers()
{
    for ( auto &player : players)
    {
        player.setIfHorse(false);
    }
    
}
int Control::getPlayerNumber()
{
    return playerNumber;
}
int Control::findPlayerIndex(const Player &player)
{
    for (int i = 0; i < players.size(); i++)
    {
        // if (players[i].getName() == player.getName())
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
void Control::setIsHorse(bool isHorse)
{
    this->isHorse = isHorse;
}
bool Control::getIsHorse()
{
    return isHorse;
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


// -- graphic functions --

void Control::startGame()
{
    currentScreen = MENU;
    // int screenWidth = 1075;
    // int screenHeight = 636;
    // InitWindow(screenWidth, screenHeight, "Rakab Game");
    // uploadThings();
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
        // askMap();
        drawSigns();
        break;
    case GAME:
        setGameBackground();
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
        break;
    }
}
void Control::setMenuBackground()
{
    DrawTexture ( myAsset.menu , 0 , 0 , WHITE );
}
void Control::setAskBackground()
{
    DrawTexture(myAsset.info, 0, 0, WHITE);//Draw the image

    TextButton goBack ;
    goBack.bounds = { 30 , 30 , 150 , 60 };
    goBack.text = "Back To MENU";

    Vector2 mousePosition = GetMousePosition();//Save the current mouse coordinates

    if (CheckCollisionPointRec(mousePosition, goBack.bounds))
    {
        // goBack.color = { 234 , 237 , 240 , 255 };// Change text color
        // goBack.buttonColor = { 101 , 107 , 110 , 200};// Change button color
        goBack.color = BLACK;
        goBack.buttonColor = { 174 , 185 , 191 , 200};

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentScreen = MENU;
        }
    } 
    else
    {
        goBack.color = { 234 , 237 , 240 , 255 };// Change text color
        goBack.buttonColor = { 101 , 107 , 110 , 200};// Change button color
        
    }

    DrawRectangleRounded (goBack.bounds , 0.4f , 0 , goBack.buttonColor);
    DrawTextEx(myAsset.listFont , goBack.text, { goBack.bounds.x + 12 , goBack.bounds.y + 20 } , 25 , 2, goBack.color);
}
void Control::setTitle()
{
    Color textColor = {4, 9, 72, 255};
    const char* text = "Rakab";
    
    DrawTextEx(myAsset.title, text, (Vector2){ 430, 50 }, 90, 2, textColor);
}
void Control::setMenuList()
{
    buttons.reserve(4);

   buttons[0].text = "New Game";
   buttons[0].bounds = { 450, 230, 250, 45 };
   
   buttons[1].text = "Load Game";
   buttons[1].bounds = { 450, 280, 250, 45 };

   buttons[2].text = "Help";
   buttons[2].bounds = { 450, 330, 250, 45 };

   buttons[3].text = "Exit";
   buttons[3].bounds = { 450, 380, 250, 45 };

    Vector2 mousePosition = GetMousePosition();

    for (int i = 0 ; i < 4 ; i++)
    {
        if (CheckCollisionPointRec(mousePosition, buttons[i].bounds)) 
        {
            // Change colors on button click
            buttons[i].buttonColor = { 0 , 0 , 0 , 110 };  // button color
            buttons[i].color = { 234 , 237 , 240 , 255 }; // text color
        }
        else 
        {
            buttons[i].color = BLACK;
            buttons[i].buttonColor = {0 , 0 , 0 , 30};
        }
    }

    // Draw button background
    // Draw button text
    DrawRectangle (buttons[0].bounds.x, buttons[0].bounds.y, buttons[0].bounds.width, buttons[0].bounds.height, buttons[0].buttonColor);
    DrawTextEx(myAsset.listFont , buttons[0].text, { buttons[0].bounds.x + 70 , buttons[0].bounds.y + 10} , 30 , 2, buttons[0].color);

    DrawRectangle (buttons[1].bounds.x, buttons[1].bounds.y, buttons[1].bounds.width, buttons[1].bounds.height, buttons[1].buttonColor);
    DrawTextEx(myAsset.listFont , buttons[1].text, { buttons[1].bounds.x + 67 , buttons[1].bounds.y + 10} , 30 , 2, buttons[1].color);

    DrawRectangle (buttons[2].bounds.x, buttons[2].bounds.y, buttons[2].bounds.width, buttons[2].bounds.height, buttons[2].buttonColor);
    DrawTextEx(myAsset.listFont , buttons[2].text, { buttons[2].bounds.width/2 + buttons[2].bounds.x - 25 , buttons[2].bounds.y + 10} , 30 , 2, buttons[2].color);

    DrawRectangle (buttons[3].bounds.x, buttons[3].bounds.y, buttons[3].bounds.width, buttons[3].bounds.height, buttons[3].buttonColor);
    DrawTextEx(myAsset.listFont , buttons[3].text, { buttons[3].bounds.width/2 + buttons[3].bounds.x - 25 , buttons[3].bounds.y + 10} , 30 , 2, buttons[3].color);

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
            system ("start C:/assets/help.pdf");
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
    Color recColor = {170 , 170 , 170 , 170}; //Background color
    float roundness = 0.3f;
    Rectangle temp = {325 , 90 , 450 , 70};

    DrawRectangleRounded ( temp , 0.3f , 0 , recColor );
    DrawTextEx( myAsset.askFont , "Choose The Number Of Players :" , { 340 , 110 } , 35 , 2 , BLACK );

    numButtons.reserve(4);

    numButtons[0].text = "3";
    numButtons[0].bounds = { 430, 200, 100, 60 };
    
    numButtons[1].text = "4";
    numButtons[1].bounds = { 550, 200, 100, 60 };
 
    numButtons[2].text = "5";
    numButtons[2].bounds = { 430, 280, 100, 60 };
 
    numButtons[3].text = "6";
    numButtons[3].bounds = { 550, 280, 100, 60 };

    Vector2 mousePosition = GetMousePosition();

    for (int i = 0 ; i < 4 ; i++)
    {
            if (CheckCollisionPointRec(mousePosition, numButtons[i].bounds)) 
            {
                // Change colors on button click
                numButtons[i].buttonColor = { 191,155,129 ,230 };
                numButtons[i].color = { 234 , 237 , 240 , 255 };
            }
            else 
            { 
                numButtons[i].buttonColor = { 141,108,88 ,170 };
                numButtons[i].color = BLACK;
            }
    }    

    for ( int i = 0 ; i < 4 ; i++ ) //Draw text and buttons
    {
        DrawRectangleRounded (numButtons[i].bounds , roundness , 0 , numButtons[i].buttonColor);
        DrawTextEx(myAsset.askFont , numButtons[i].text, { numButtons[i].bounds.x + 40 , numButtons[i].bounds.y + 10 } , 30 , 2, numButtons[i].color);
    }

    for (int i = 0; i < 4; i++)
    {
      if (CheckCollisionPointRec(mousePosition, numButtons[i].bounds))
      {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            setPlayerNumber(i + 3);//Set the number of players
            currentScreen = INFO; //Change the screen to the information screen
            break;
        }
      }
    }  
}
void Control::drawInput()
{
    static int counter = 1 ; //Player number

    if (counter <= getPlayerNumber())
    {
        Color backColor = { 108,194,237 , 200 };

        char text[2] ; 
        text[0] = counter + '0'; // player number (Convert character to number)
        text[1] = '\0'; //end

        Rectangle back = { 500 , 70 , 150 , 70 };
        DrawRectangleRounded ( back , 0.4f , 0 , backColor);
        DrawRectangleRoundedLines(back, 0.4f, 0, 3, { 6 , 87 , 128 , 255 }); 
        DrawTextEx ( myAsset.inputFont , "Player" , { 525 , 90 } , 25 , 2 , { 28,52,40, 255 });
        DrawTextEx ( myAsset.inputFont , text , { 615 , 90 } , 25 , 2 , { 28,52,40, 255 } );

        inputName.DrawName();

        inputAge.DrawAge();
    
        submit.bounds = { 500 , 420 , 150 , 70 };
        submit.text = "NEXT";

        Vector2 mousePosition = GetMousePosition();

        if (CheckCollisionPointRec(mousePosition, submit.bounds))
        {
            submit.color = WHITE;
            submit.buttonColor = {137,162,97, 180};
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
            submit.color = { 28,52,40, 255 };
            submit.buttonColor = { 188,206,170, 180};
        }
        DrawRectangleRounded (submit.bounds , 0.4f , 0 , submit.buttonColor);//draw next button
        DrawTextEx(myAsset.inputFont , submit.text, { submit.bounds.x + 45 , submit.bounds.y + 20 } , 25 , 2, submit.color);
    }
    else currentScreen = MAP; //Transfer to the game screen

}
void Control::updateInput()
{
    inputName.Update();
    inputAge.Update();
}
void Control::askMap()
{
    const char* playerName = youngestPlayer().getName();

    DrawTexture(myAsset.game, 0, 0, WHITE); // background image
    DrawTextureEx(myAsset.map, (Vector2){200, 75}, 0.0f, 0.5f, WHITE); //Map image

    TextButton goGame ;
    goGame.bounds = { 10, 12 , 150 , 60 };
    goGame.text = "Back To GAME";

    Vector2 mousePosition = GetMousePosition();//Save the current mouse coordinates

    if (CheckCollisionPointRec(mousePosition, goGame.bounds))
    {
        goGame.color = WHITE;
        goGame.buttonColor = { 174 , 185 , 191 , 200};

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentScreen = GAME;
        }
    } 
    else
    {
        goGame.color = WHITE;// Change text color
        goGame.buttonColor = { 0,61,59 , 200};// Change button color
    }

    DrawRectangleRounded (goGame.bounds , 0.4f , 0 , goGame.buttonColor);
    DrawTextEx(myAsset.listFont , goGame.text, { goGame.bounds.x + 12 , goGame.bounds.y + 20 } , 25 , 2, goGame.color);
   
    DrawTextEx(myAsset.askFont , playerName , {500 , 15} , 30 , 2 , BLACK); // Print the name of the player
    DrawTextEx(myAsset.askFont , " Choose The War Place!" , {380 , 35} , 30 , 2 , BLACK);
    DrawTextEx(myAsset.askFont , " Click On The Sign To Select  " , {380 , 580} , 30 , 2 , BLACK);
   // selectWarPlace(players[0]);
    selectWarPlace(youngestPlayer());
}
void Control::drawSigns()
{
    for (int i = 0; i < getProvinceNumber(); i++ )
    {
        DrawCircle(signs[i].position.x, signs[i].position.y, 11, signs[i].color);
    }
    
}

void Control::setGameBackground()
{
    DrawTexture(myAsset.table, 0, 0, WHITE);

    TextButton goMap;
    goMap.bounds = { 7, 13, 60, 60 };
    goMap.text = "MAP";

    Vector2 position = { 239, 607 };
    if (players.size() > 0 && players[0].getName() && strlen(players[0].getName()) > 0) {
        // Draw bold effect for player 0
        DrawTextEx(myAsset.name, players[0].getName(), { position.x - 1, position.y }, 30, 2, BLACK);  // Draw shadow
        DrawTextEx(myAsset.name, players[0].getName(), { position.x + 1, position.y }, 30, 2, BLACK);  // Draw shadow
        DrawTextEx(myAsset.name, players[0].getName(), { position.x, position.y - 1 }, 30, 2, BLACK);  // Draw shadow
        DrawTextEx(myAsset.name, players[0].getName(), { position.x, position.y + 1 }, 30, 2, BLACK);  // Draw shadow
        // Draw the text in the original position
        DrawTextEx(myAsset.name, players[0].getName(), position, 30, 2, WHITE);  // Draw main text
    }

    position = { 770, 607 };
    if (players.size() > 1 && players[1].getName() && strlen(players[1].getName()) > 0) {
        // Draw bold effect for player 1
        DrawTextEx(myAsset.name, players[1].getName(), { position.x - 1, position.y }, 30, 2, BLACK);  
        DrawTextEx(myAsset.name, players[1].getName(), { position.x + 1, position.y }, 30, 2, BLACK);  
        DrawTextEx(myAsset.name, players[1].getName(), { position.x, position.y - 1 }, 30, 2, BLACK);  
        DrawTextEx(myAsset.name, players[1].getName(), { position.x, position.y + 1 }, 30, 2, BLACK);  
        DrawTextEx(myAsset.name, players[1].getName(), position, 30, 2, WHITE); 
    }

    position = { 1045, 330 };
    Vector2 origin = { 0, 0 };
    float rotation = -90.0f; 
    if (players.size() > 2 && players[2].getName() && strlen(players[2].getName()) > 0) {
        // Draw bold effect for player 2
        DrawTextPro(myAsset.name, players[2].getName(), { position.x - 1, position.y }, origin, rotation, 30, 2, BLACK);  
        DrawTextPro(myAsset.name, players[2].getName(), { position.x + 1, position.y }, origin, rotation, 30, 2, BLACK);  
        DrawTextPro(myAsset.name, players[2].getName(), { position.x, position.y - 1 }, origin, rotation, 30, 2, BLACK);  
        DrawTextPro(myAsset.name, players[2].getName(), { position.x, position.y + 1 }, origin, rotation, 30, 2, BLACK);  
        DrawTextPro(myAsset.name, players[2].getName(), position, origin, rotation, 30, 2, WHITE);
    }

    if (players.size() > 3) {
        const char* playerName3 = players[3].getName();
        if (playerName3 && strlen(playerName3) > 0) {
            position = { 810, 29 };
            origin = { 0, 0 };
            rotation = -180.0f; 
            DrawTextPro(myAsset.name, playerName3, { position.x - 1, position.y }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName3, { position.x + 1, position.y }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName3, { position.x, position.y - 1 }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName3, { position.x, position.y + 1 }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName3, position, origin, rotation, 30, 2, WHITE);
        }
    }

    if (players.size() > 4) {
        const char* playerName4 = players[4].getName();
        if (playerName4 && strlen(playerName4) > 0) {
            position = { 280, 31 };
            origin = { 0, 0 };
            rotation = -180.0f; 
            DrawTextPro(myAsset.name, playerName4, { position.x - 1, position.y }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName4, { position.x + 1, position.y }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName4, { position.x, position.y - 1 }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName4, { position.x, position.y + 1 }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName4, position, origin, rotation, 30, 2, WHITE);
        }
    }

    if (players.size() > 5) {
        const char* playerName5 = players[5].getName();
        if (playerName5 && strlen(playerName5) > 0) {
            position = { 30, 280 };
            origin = { 0, 0 };
            rotation = 90.0f; 
            DrawTextPro(myAsset.name, playerName5, { position.x - 1, position.y }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName5, { position.x + 1, position.y }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName5, { position.x, position.y - 1 }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName5, { position.x, position.y + 1 }, origin, rotation, 30, 2, BLACK);  
            DrawTextPro(myAsset.name, playerName5, position, origin, rotation, 30, 2, WHITE);
        }
    }

    Vector2 mousePosition = GetMousePosition(); // Save the current mouse coordinates

    if (CheckCollisionPointRec(mousePosition, goMap.bounds))
    {
        goMap.color = WHITE;
        goMap.buttonColor = { 255,248,158, 200};

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentScreen = MAP;
        }
    } 
    else
    {
        goMap.color = WHITE; // Change text color
        goMap.buttonColor = { 255, 250, 183, 170 }; // Change button color
    }

    DrawRectangleRounded(goMap.bounds, 0.4f, 0, goMap.buttonColor);
    DrawTextEx(myAsset.listFont, goMap.text, { goMap.bounds.x + 12, goMap.bounds.y + 20 }, 25, 2, goMap.color);
}




void Control::DrawMousePosition() {
    // دریافت موقعیت موس
    Vector2 mousePosition = GetMousePosition();
    
    // تبدیل موقعیت موس به رشته
    char positionText[64];
    sprintf(positionText, "Mouse X: %d, Y: %d", (int)mousePosition.x, (int)mousePosition.y);
    
    // رسم موقعیت موس در گوشه بالای صفحه
    DrawText(positionText, 10, 10, 20, BLACK);
}