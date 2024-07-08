#include <iostream>
#include <algorithm>
#include <memory>
#include <typeinfo>
#include <unistd.h>

#include "player.h"
#include "card.h"
#include "purple.h"
#include "yellow.h"
#include "scarecrow.h"
#include "princes.h"
#include "map.h"
#include "leader.h"


struct SharedPtrCompare
{ // To compare two shred_pointers
    template <class T, class U>
    bool operator()(const std::shared_ptr<T> &lhs, const std::shared_ptr<U> &rhs) const
    {
        return *lhs == *rhs;
    }
};

Player::Player() { scorePlayer = 0; };
Player::Player(int age, std::string name, std::string color)
{
    setAge(age);
    setName(name);
    setColor(color);
}
void Player::setName(std::string name)
{
    this->name = name;
}
void Player::setAge(int age)
{
    this->age = age;
}
void Player::setColor(std::string color)
{
    this->color = color;
}
void Player::addCard(std::shared_ptr<Card> card)
{
    hand.push_back(card);
}
void Player::showHandCards()
{
    for (int i = 0; i < hand.size(); i++)
    {
        std::cout << hand[i]->getName() << " --- ";
    }
    std::cout << std::endl;
}
void Player::addProvinces(std::string province)
{
    capturedProvinces.push_back(province);
}
void Player::selectCard()
{
    std::shared_ptr<Card> card;
    std::string tempName;
    bool found = true;
    do
    {
        if (found == true) // for the first time
            std::cout << " Enter Your Chosen Card : ";

        std::cin >> tempName;

        if (tempName.length() <= 2) // Detection of yellow or purple card
            card = std::make_shared<YellowCard>(tempName);
        else
            card = std::make_shared<PurpleCard>(tempName);

        if (tempName == "leader")
        {
            // leaderCard leader;
            // leader.useCard();
        }

        else if (tempName == "scarecrow")
        {
            if (yellowCards.size() != 0)
            {
                ScarecrowCard scarecrow;
                scarecrow.useThisCard(*this); // we want to use useCard for current player
            }
        }
        else if (tempName == "spring" || tempName == "winter")
        {
            setSeason(tempName);
        }

        auto elementFound = std::find_if(hand.begin(), hand.end(), [&card](const std::shared_ptr<Card> &c)
                                         { return *c == *card; });
        // Find the selected card in the player's hand (c is the current element in hand)

        if (elementFound != hand.end()) // If found
        {
            found = true; // Exit the loop
            hand.erase(elementFound);
            usedCards.push_back(card);
        }
        else
        {
            std::cout << " ERROR: Please Enter Valid Card: " << std::endl;
            found = false;
        }
    } while (!found);
}
void Player::setSeason(std::string season)
{
    this->season = season;
}
void Player::showUsedCards()
{
    std::cout << getName() << " : ";
    if (usedCards.size() > 0)
    {
        for (int i = 0; i < usedCards.size(); i++)
        {
            std::cout << usedCards[i]->getName() << " - ";
        }
    }
    std::cout << std::endl;
}
void Player::recognizeYellow()
{
    yellowCards.resize(0);
    for (const auto &usedCard : usedCards)
    {
        if (std::dynamic_pointer_cast<YellowCard>(usedCard))
        {
            yellowCards.push_back(usedCard);
        }
    }
}
void Player::showYcard()
{
    for (const auto &usedYcard : yellowCards)
    {
        std::cout << usedYcard->getName() << " --- ";
    }
}
void Player::setScorePlayer(int scorePlayer)
{
    this->scorePlayer = scorePlayer;
}
void Player::setPass(bool pass)
{
    this->pass = pass;
}
void Player::yellowInScore()
{
    int sum = 0;
    recognizeYellow();
    for (auto card : yellowCards)
    {
        sum += stoi(card->getName());
    }
    setScorePlayer(sum);
}
void Player::burnCardsPlayer()
{
    burnedCards.insert(burnedCards.end(), usedCards.begin(), usedCards.end()); // Add elements to the end of the vector
    usedCards.resize(0);                                                       // Remove used cards
}
void Player::burnHand()
{
    burnedCards.insert(burnedCards.end(), hand.begin(), hand.end());
    hand.resize(0); // Remove hand cards
}
void Player::showCapturedProvinces()
{
    std::cout << " ---> " << getName() << " : ";
    for (int i = 0; i < capturedProvinces.size(); i++)
    {
        std::cout << capturedProvinces[i] << " - ";
    }
    std::cout << '\n';
}
int Player::getAge() const
{
    return age;
}
int Player::getScorePlayer()
{
    return scorePlayer;
}
int Player::maxYcards()
{
    std::vector<int> yellowIntegers;
    for (auto card : yellowCards)
    {
        yellowIntegers.push_back(stoi(card->getName()));
    }
    auto maxElement = std::max_element(yellowIntegers.begin(), yellowIntegers.end()); // Find the largest element using the max_element function
    return (*maxElement);                                                             // To access the pointer value, not the pointer itself
}
int Player::numCardsOfPlayer()
{
    return (10 + getNumProvinces());
}
int Player::numberOfPrinces()
{
    int counter = 0;

    for (auto card : usedCards)
    {
        if (card->getName() == "princes")
            counter++;
    }
    return counter;
}
int Player::getHandSize()
{
    return hand.size();
}
int Player::getNumProvinces()
{
    return (capturedProvinces.size());
}
bool Player::hasYellowCard()
{
    for (const auto &card : hand)
    {
        if (std::dynamic_pointer_cast<YellowCard>(card))
        {
            return true;
        }
    }
    return false;
}
bool Player::hasPurpleCard()
{
    for (const auto &card : hand)
    {
        if (std::dynamic_pointer_cast<PurpleCard>(card))
        {
            return true;
        }
    }
    return false;
}
bool Player::ifBurn()
{
    char response;
    if (!hasYellowCard() && hasPurpleCard())
    {
        std::cout << "\n\n " << getName() << " You Have No Yellow Card!!! ";
        std::cout << "\n Do You Want To Burn Your Cards? (Y/N) ";
        std::cin >> response;
    }
    if (response == 'Y')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Player::isFind(std::shared_ptr<Card> Ycard)
{
    auto elementFound = std::find_if(yellowCards.begin(), yellowCards.end(), [Ycard](const std::shared_ptr<Card> &card)
                                     { return *card == *Ycard; });
    if (elementFound != yellowCards.end())
    {
        hand.push_back(Ycard);
        usedCards.erase(std::remove(usedCards.begin(), usedCards.end(), *elementFound), usedCards.end());
        // The remove function moves all the elements equal to elementFound to the end of the vector
        // then the erase function deletes all of them
        return true;
    }
    else
    {
        return false;
    }
}
bool Player::hasDrummer()
{
    std::shared_ptr<Card> card = std::make_shared<PurpleCard>("drummer");

    auto elementFound = std::find_if(usedCards.begin(), usedCards.end(),
                                     [&card](const std::shared_ptr<Card> &ptr)
                                     { return SharedPtrCompare()(ptr, card); });

    if (elementFound != usedCards.end())
    {
        return true;
    }
    else
        return false;
}
bool Player::hasPrinces()
{
    std::shared_ptr<Card> card = std::make_shared<PurpleCard>("princes");

    auto elemenFound = std::find_if(usedCards.begin(), usedCards.end(),
                                    [&card](const std::shared_ptr<Card> &ptr)
                                    { return SharedPtrCompare()(ptr, card); });

    if (elemenFound != usedCards.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Player::getPass()
{
    return pass;
}
// bool Player::winGame()
// {
//     int CapturedProvinces = 0;
//     Map map;
//     map.readMatrix();
//     map.readUnorderedMap();
//     for (int i = 0 ; i < getNumProvinces() ; i++)
//     {
//        for (int j = i + 1 ; j < getNumProvinces() ; j++)
//        {
//          if (map.checkAdjacent(capturedProvinces[i], capturedProvinces[j])) //Proximity detection
//          {
//              CapturedProvinces++;
//          }
//        }
//     }
//     if ( CapturedProvinces == 3 || getNumProvinces() == 5 )
//     {
//          return true;
//     }
//         return false;

// }
bool Player::isProximity()
{
    Map map;
    int CapturedProvinces = 0;
    for (int i = 0; i < getNumProvinces(); i++)
    {
        for (int j = i + 1; j < getNumProvinces(); j++)
        {
            if (map.checkAdjacent(capturedProvinces[i], capturedProvinces[j])) // Proximity detection
            {
                CapturedProvinces++;
            }
        }
    }
    if (CapturedProvinces == 3)
    {
        return true;
    }
    return false;
}
std::string Player::getSeason()
{
    return season;
}
std::string Player::getName() const
{
    return name;
}
std::string Player::getColor() const
{
    return color;
}
std::vector<std::shared_ptr<Card>> &Player::getHandCards()
{
    return hand;
}
std::vector<std::shared_ptr<Card>> &Player::getBurnedCards()
{
    return burnedCards;
}
std::vector<std::shared_ptr<Card>> Player::getYcards()
{
    return yellowCards;
}
