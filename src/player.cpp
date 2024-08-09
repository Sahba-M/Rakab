#include <iostream>
#include <algorithm>
#include <memory>
#include <typeinfo>
#include <unistd.h>
#include <raylib.h>

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
Player::Player(int age, const char *name, Color color)
{
    setAge(age);
    setName(name);
    setColor(color);
}
void Player::setName(const char *name)
{
    strncpy(this->name, name, 25); // It copies 25 characters inside name
}
void Player::setAge(int age)
{
    this->age = age;
}
void Player::setColor(Color color)
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
    std::cout << "test province : " << province << std::endl;
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
            setIfLeader(true);
        }
        else if (tempName == "horse")
        {
            setIfHorse(true);
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
void Player::setIfLeader(bool ifLeader)
{
    this->ifLeader = ifLeader;
}
void Player::setIfHorse(bool ifHorse)
{
    this->ifHorse = ifHorse;
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
            std::cout << name <<"---";
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
    std::cout << "burn hand\n";
    hand.resize(0); // Remove hand cards
    std::cout << "size hand:" << hand.size() << std::endl;
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
void Player::insertBurnedCard(std::vector<std::shared_ptr<Card>> &cards)
{
    cards.insert(cards.end(), burnedCards.begin(), burnedCards.end()); // for all player
}
void Player::insertHandCard(std::vector<std::shared_ptr<Card>> &cards)
{
    cards.insert(cards.end(), hand.begin(), hand.end()); // for all player
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
                                                                                      // To access the pointer value, not the pointer itself
    return (*maxElement);
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
int Player::numberOfDrummer()
{
    int counter = 0;

    for (auto card : usedCards)
    {
        if (card->getName() == "drummer")
            counter++;
    }
    return counter;
}
int Player::numberOfVirago()
{
    int counter = 0;

    for (auto card : usedCards)
    {
        if (card->getName() == "virago")
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
int Player::numberOfMaxYcards()
{
    int counter = 0;
    for (int i = 0; i < yellowCards.size(); i++)
    {
        if (stoi(yellowCards[i]->getName()) == maxYcards())
        {
            counter++;
        }
    }
    return counter;
}
bool Player::hasYellowGround()
{
    for (const auto &card : usedCards)
    {
        if (std::dynamic_pointer_cast<YellowCard>(card))
        {
            return true;
        }
    }
    return false;
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
int Player::ifBurn(AssetManager &myAsset)
{
    
    if (!hasYellowCard() && hasPurpleCard())
    {

       DrawTexture(myAsset.winner, 0, 0, WHITE);
    //    std::cout << "test after back\n";

       DrawTextEx(myAsset.askFont, getName(), {512, 164}, 50, 2, WHITE);
       DrawTextEx(myAsset.askFont, " DO YOU WANT TO BURN YOUR CARDS ? ", {220, 250}, 50, 2, WHITE);
    //    std::cout << "test after ask\n";

       Button yesButton;
       Button noButton;

    //    yesButton.buttonColor = {81, 204, 65, 255};
    //    noButton.buttonColor = {196, 69, 84, 255};

       yesButton.text = "YES";
       yesButton.bounds = {440, 360, 70, 70};
       noButton.text = "NO";
       noButton.bounds = {550, 360, 70, 70};


       Vector2 mousePosition = GetMousePosition(); // Save the current mouse coordinates

        if (CheckCollisionPointRec(mousePosition, yesButton.bounds))
        {
            yesButton.color = WHITE;
            yesButton.buttonColor = {35, 122, 23, 255};

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
               return 1;
            }
        }
        else
        {
            yesButton.color = BLACK ; // Change text color
            yesButton.buttonColor = {81, 204, 65, 255}; // Change butto
        }

        mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, noButton.bounds))
        {
            noButton.color = WHITE;
            noButton.buttonColor = {138, 18, 32, 255};

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                return 0;
            }
        }
        else
        {
            noButton.color = BLACK; // Change text color
            noButton.buttonColor = {196, 69, 84, 255}; // Change butto
        }

       DrawRectangleRounded(yesButton.bounds, 0.3f, 0, yesButton.buttonColor);
       DrawTextEx(myAsset.listFont, yesButton.text, {yesButton.bounds.x + 15, yesButton.bounds.y + 25}, 30, 2, yesButton.color);

       DrawRectangleRounded(noButton.bounds, 0.3f, 0, noButton.buttonColor);
       DrawTextEx(myAsset.listFont, noButton.text, {noButton.bounds.x + 20, noButton.bounds.y + 25}, 30, 2, noButton.color);

    }
    return -1;
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

    auto elementFound = std::find_if(usedCards.begin(), usedCards.end(), [&card](const std::shared_ptr<Card> &ptr)
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

    auto elemenFound = std::find_if(usedCards.begin(), usedCards.end(), [&card](const std::shared_ptr<Card> &ptr)
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
bool Player::getIfHorse()
{
    return ifHorse;
}
bool Player::hasHorse()
{
    std::shared_ptr<Card> card = std::make_shared<PurpleCard>("horse");

    auto elemenFound = std::find_if(usedCards.begin(), usedCards.end(), [&card](const std::shared_ptr<Card> &ptr)
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
bool Player::hasVirago()
{
    std::shared_ptr<Card> card = std::make_shared<PurpleCard>("virago");

    auto elemenFound = std::find_if(usedCards.begin(), usedCards.end(), [&card](const std::shared_ptr<Card> &ptr)
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
bool Player::hasDean()
{
    std::shared_ptr<Card> card = std::make_shared<PurpleCard>("dean");

    auto elemenFound = std::find_if(usedCards.begin(), usedCards.end(), [&card](const std::shared_ptr<Card> &ptr)
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
bool Player::isProximity(Map &map)
{
    std::cout << "is proximity\n";
   
    int CapturedProvinces = 0;
    for (int i = 0; i < getNumProvinces(); i++)
    {
        for (int j = i + 1; j < getNumProvinces(); j++)
        {
            if (map.checkAdjacent(capturedProvinces[i], capturedProvinces[j])) // Proximity detection
            {
                std::cout << "if proximity\n";
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
bool &Player::getIfLeader()
{
    return ifLeader;
}
std::string Player::getSeason()
{
    return season;
}
const char *Player::getName()
{
    return name;
}
Color Player::getColor() const
{
    return color;
}
std::vector<std::shared_ptr<Card>> Player::getYcards()
{
    return yellowCards;
}
std::istream &operator>>(std::istream &input, Player &player)
{
    // std::string color;
    char *name;

    bool pass;

    int age, size;

    std::vector<std::string> provinces;

    std::vector<std::shared_ptr<Card>> cards;

    input >> name;
    player.setName(name);

    input >> age;
    player.setAge(age);

    // input >> color;
    // player.setColor(color);

    input >> size;
    for (int i = 0; i < size; i++)
    {
        input >> provinces[i];
        player.capturedProvinces[i] = provinces[i];
    }

    input >> size;
    for (int i = 0; i < size; i++)
    {
        input >> cards[i];
        player.hand[i] = cards[i];
    }

    input >> size;
    for (int i = 0; i < size; i++)
    {
        input >> cards[i];
        player.usedCards[i] = cards[i];
    }

    input >> size;
    for (int i = 0; i < size; i++)
    {
        input >> cards[i];
        player.burnedCards[i] = cards[i];
    }

    input >> size;
    for (int i = 0; i < size; i++)
    {
        input >> cards[i];
        player.yellowCards[i] = cards[i];
    }

    input >> pass;
    player.setPass(pass);

    return input;
}
std::ostream &operator<<(std::ostream &output, Player &player)
{
    output << player.name << "\n";
    // output << player.age << " " << player.color << "\n";
    output << player.capturedProvinces.size() << "\n";
    for (int i = 0; i < player.capturedProvinces.size(); i++)
    {
        output << player.capturedProvinces[i] << " ";
    }
    output << player.hand.size() << "\n";
    for (int i = 0; i < player.hand.size(); i++)
    {
        output << *player.hand[i] << " ";
    }
    output << player.usedCards.size() << "\n";
    for (int i = 0; i < player.usedCards.size(); i++)
    {
        output << *player.usedCards[i] << " ";
    }
    output << player.burnedCards.size() << "\n";
    for (int i = 0; i < player.burnedCards.size(); i++)
    {
        output << *player.burnedCards[i] << " ";
    }
    output << player.yellowCards.size() << "\n";
    for (int i = 0; i < player.yellowCards.size(); i++)
    {
        output << *player.yellowCards[i] << " ";
    }
    output << '\n'
           << player.pass << "\n";

    return output;
}
void Player::drawCards(int x, int y, AssetManager &myAsset, Vector2 origin, float rotation)
{
    int i = 0;
    for (auto card : hand)
    {
        std::string name = card->getName();
        Texture2D texture;

        if (name == "1")
            texture = myAsset.soldier1;
        else if (name == "2")
            texture = myAsset.soldier2;
        else if (name == "3")
            texture = myAsset.soldier3;
        else if (name == "4")
            texture = myAsset.soldier4;
        else if (name == "5")
            texture = myAsset.soldier5;
        else if (name == "6")
            texture = myAsset.soldier6;
        else if (name == "10")
            texture = myAsset.soldier10;
        else if (name == "spring")
            texture = myAsset.spring;
        else if (name == "winter")
            texture = myAsset.winter;
        else if (name == "leader")
            texture = myAsset.leader;
        else if (name == "princes")
            texture = myAsset.princes;
        else if (name == "dean")
            texture = myAsset.dean;
        else if (name == "drummer")
            texture = myAsset.drummer;
        else if (name == "virago")
            texture = myAsset.virago;
        else if (name == "scarecrow")
            texture = myAsset.scarecrow;
        else if (name == "horse")
            texture = myAsset.horse;

        Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
        Vector2 position = {static_cast<float>(x) + static_cast<float>(i * 25), static_cast<float>(y)};
        Rectangle destRec = {position.x, position.y, (float)texture.width, (float)texture.height};

        DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);
        i++;
    }
}
void Player::drawCardSpecialPlayer(int x, int y, AssetManager &myAsset, Vector2 origin, float rotation)
{
    int i = 0;

    for (auto card : hand)
    {
        std::string name = card->getName();
        Texture2D texture;

        if (name == "1")
            texture = myAsset.soldier1;
        else if (name == "2")
            texture = myAsset.soldier2;
        else if (name == "3")
            texture = myAsset.soldier3;
        else if (name == "4")
            texture = myAsset.soldier4;
        else if (name == "5")
            texture = myAsset.soldier5;
        else if (name == "6")
            texture = myAsset.soldier6;
        else if (name == "10")
            texture = myAsset.soldier10;
        else if (name == "spring")
            texture = myAsset.spring;
        else if (name == "winter")
            texture = myAsset.winter;
        else if (name == "leader")
            texture = myAsset.leader;
        else if (name == "princes")
            texture = myAsset.princes;
        else if (name == "dean")
            texture = myAsset.dean;
        else if (name == "drummer")
            texture = myAsset.drummer;
        else if (name == "virago")
            texture = myAsset.virago;
        else if (name == "scarecrow")
            texture = myAsset.scarecrow;
        else if (name == "horse")
            texture = myAsset.horse;

        Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
        Vector2 position = {static_cast<float>(x), static_cast<float>(y) + static_cast<float>(i * 25)};
        Rectangle destRec = {position.x, position.y, (float)texture.width, (float)texture.height};

        DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);

        i++;
    }
}
void Player::drawBackCards(int x, int y, AssetManager &myAsset, Vector2 origin, float rotation)
{
    int i = 0;
    for (auto card : hand)
    {
        std::string name = card->getName();
        Texture2D texture = myAsset.back;

        Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
        Vector2 position = {static_cast<float>(x) + static_cast<float>(i * 25), static_cast<float>(y)};
        Rectangle destRec = {position.x, position.y, (float)texture.width, (float)texture.height};

        DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);

        i++;
    }
}
void Player::drawUseCards(int x, int y, AssetManager &myAsset, Vector2 origin, float rotation)
{
    int i = 0;

    for (auto card : usedCards)
    {
        std::string name = card->getName();
        Texture2D texture;

        if (name == "1")
            texture = myAsset.soldier1;
        else if (name == "2")
            texture = myAsset.soldier2;
        else if (name == "3")
            texture = myAsset.soldier3;
        else if (name == "4")
            texture = myAsset.soldier4;
        else if (name == "5")
            texture = myAsset.soldier5;
        else if (name == "6")
            texture = myAsset.soldier6;
        else if (name == "10")
            texture = myAsset.soldier10;
        else if (name == "spring" || name == "winter")
        {
            showSeason(name == "spring" ? myAsset.spring : myAsset.winter);
            i++;
            continue;
        }
        else if (name == "leader")
            texture = myAsset.leader;
        else if (name == "princes")
            texture = myAsset.princes;
        else if (name == "dean")
            texture = myAsset.dean;
        else if (name == "drummer")
            texture = myAsset.drummer;
        else if (name == "virago")
            texture = myAsset.virago;
        else if (name == "scarecrow")
        {
            texture = myAsset.scarecrow;
            // Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
            // Vector2 position = {static_cast<float>(x) + static_cast<float>(i * 25), static_cast<float>(y)};
            // Rectangle destRec = {position.x, position.y, (float)texture.width, (float)texture.height};
            // DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);

            // recognizeYellow();
            // if (yellowCards.size() != 0)
            // {
            //     updateYellowDown(x, y, 70, 108);

            // }

            // i++;
            // continue;
        }
        else if (name == "horse")
            texture = myAsset.horse;

        if (!texture.id)
            continue; // Ensure texture is valid

        Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
        Vector2 position = {static_cast<float>(x) + static_cast<float>(i * 25), static_cast<float>(y)};
        Rectangle destRec = {position.x, position.y, (float)texture.width, (float)texture.height};

        DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);
        i++;
    }
}
void Player::drawUseCardSpecialPlayer(int x, int y, AssetManager &myAsset, Vector2 origin, float rotation)
{
    int i = 0;

    for (auto card : usedCards)
    {
        std::string name = card->getName();
        Texture2D texture;

        if (name == "1")
            texture = myAsset.soldier1;
        else if (name == "2")
            texture = myAsset.soldier2;
        else if (name == "3")
            texture = myAsset.soldier3;
        else if (name == "4")
            texture = myAsset.soldier4;
        else if (name == "5")
            texture = myAsset.soldier5;
        else if (name == "6")
            texture = myAsset.soldier6;
        else if (name == "10")
            texture = myAsset.soldier10;
        else if (name == "spring" || name == "winter")
        {
            showSeason(name == "spring" ? myAsset.spring : myAsset.winter);
            i++;
            continue;
        }
        else if (name == "leader")
            texture = myAsset.leader;
        else if (name == "princes")
            texture = myAsset.princes;
        else if (name == "dean")
            texture = myAsset.dean;
        else if (name == "drummer")
            texture = myAsset.drummer;
        else if (name == "virago")
            texture = myAsset.virago;
        else if (name == "scarecrow")
            texture = myAsset.scarecrow;
        else if (name == "horse")
            texture = myAsset.horse;

        if (!texture.id)
            continue;

        Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
        Vector2 position = {static_cast<float>(x), static_cast<float>(y) + static_cast<float>(i * 25)};
        Rectangle destRec = {position.x, position.y, (float)texture.width, (float)texture.height};

        DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);

        i++;
    }
}
void Player::drawBackCardSpecialPlayer(int x, int y, AssetManager &myAsset, Vector2 origin, float rotation)
{
    int i = 0;

    for (auto card : hand)
    {
        std::string name = card->getName();
        Texture2D texture = myAsset.back;

        Rectangle sourceRec = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
        Vector2 position = {static_cast<float>(x), static_cast<float>(y) + static_cast<float>(i * 25)};
        Rectangle destRec = {position.x, position.y, (float)texture.width, (float)texture.height};

        DrawTexturePro(texture, sourceRec, destRec, origin, rotation, WHITE);

        i++;
    }
}
void Player::updateCardsDown(int x, int y, int cardWidth, int cardHeight, bool &turn)
{
        Vector2 mousePosition = GetMousePosition();
        for (size_t i = hand.size(); i > 0; i--)
        {
            std::string name = hand[i - 1]->getName();

            Rectangle cardRect = {static_cast<float>(x + (i - 1) * 25), static_cast<float>(y), static_cast<float>(cardWidth), static_cast<float>(cardHeight)};

            if (CheckCollisionPointRec(mousePosition, cardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                
                if (hand[i - 1]->getName() == "winter")
                {
                    setSeason(hand[i - 1]->getName());
                }
                else if (hand[i - 1]->getName() == "spring")
                {
                    setSeason(hand[i - 1]->getName());
                }
                else if (hand[i - 1]->getName() == "leader")
                {
                    setIfLeader(true);
                }
                else if (hand[i - 1]->getName() == "horse")
                {
                    setIfHorse(true);
                }
                else if (hand[i - 1]->getName() == "scarecrow")
                {
                    setIfSscarecrow(true);
                    usedCards.push_back(hand[i - 1]);
                    hand.erase(hand.begin() + (i - 1));
                    
                    turn = false;
                    return;
                }
                else if (hand[i - 1]->getName() == "dean")
                {
                    setIfDean(true);
                }
                usedCards.push_back(hand[i - 1]);
                hand.erase(hand.begin() + (i - 1));
                turn = true;


                return;
            }
        }
    
}
void Player::updateYellowDown(int x, int y, int cardWidth, int cardHeight, bool &turn)
{
    // std::cout << "test in function " << std::endl;
    Vector2 mousePosition = GetMousePosition();
    for (int i = usedCards.size(); i > 0; i--)
    {
        std::string name = usedCards[i - 1]->getName();
        Rectangle cardRect = {static_cast<float>(x + (i - 1) * 25), static_cast<float>(y), static_cast<float>(cardWidth), static_cast<float>(cardHeight)};

        if (CheckCollisionPointRec(mousePosition, cardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            hand.push_back(usedCards[i - 1]);
            usedCards.erase(usedCards.begin() + (i - 1));
            turn = true;
            setIfSscarecrow(false);
            break;
        }
    }
    // setIfSscarecrow(false);
     
}

void Player::updateCardsTop(int x, int y, int cardWidth, int cardHeight, bool &turn)
{
    Vector2 mousePosition = GetMousePosition();

    for (size_t i = hand.size(); i > 0; i--)
    {
        std::string name = hand[i - 1]->getName();

        Rectangle cardRect = {static_cast<float>(x - 60 + (i - 1) * 25), static_cast<float>(y - 115), static_cast<float>(cardWidth), static_cast<float>(cardHeight)};

        if (CheckCollisionPointRec(mousePosition, cardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

            if (hand[i - 1]->getName() == "winter")
            {
                setSeason(hand[i - 1]->getName());
            }
            else if (hand[i - 1]->getName() == "spring")
            {
                setSeason(hand[i - 1]->getName());
            }
            else if (hand[i - 1]->getName() == "leader")
            {
                setIfLeader(true);
            }
            else if (hand[i - 1]->getName() == "horse")
            {
                setIfHorse(true);
            }
            else if (hand[i - 1]->getName() == "scarecrow")
            {
                setIfSscarecrow(true);
                usedCards.push_back(hand[i - 1]);
                hand.erase(hand.begin() + (i - 1));
                turn = false;

                return;
            }
            else if (hand[i - 1]->getName() == "dean")
            {
                setIfDean(true);
            }

            usedCards.push_back(hand[i - 1]);
            hand.erase(hand.begin() + (i - 1));
            turn = true;

            return;
        }
    }
}
void Player::updateYellowTop(int x, int y, int cardWidth, int cardHeight, bool &turn)
{
    Vector2 mousePosition = GetMousePosition();
    for (int i = usedCards.size(); i > 0; i--)
    {
        std::string name = usedCards[i - 1]->getName();
        Rectangle cardRect = {static_cast<float>(x - 60 + (i - 1) * 25), static_cast<float>(y - 115), static_cast<float>(cardWidth), static_cast<float>(cardHeight)};

        if (CheckCollisionPointRec(mousePosition, cardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            hand.push_back(usedCards[i - 1]);
            usedCards.erase(usedCards.begin() + (i - 1));
            turn = true;
            setIfSscarecrow(false);
            break;
        }
    }
}

void Player::updateCardsSpecialR(int x, int y, int cardWidth, int cardHeight, bool &turn)
{
    Vector2 mousePosition = GetMousePosition();

    for (size_t i = hand.size(); i > 0; i--)
    {
        std::string name = hand[i - 1]->getName();

        Rectangle cardRect = {static_cast<float>(x), static_cast<float>(y - 80 + (i - 1) * 25), static_cast<float>(cardWidth), static_cast<float>(cardHeight)};

        if (CheckCollisionPointRec(mousePosition, cardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (hand[i - 1]->getName() == "winter")
            {
                setSeason(hand[i - 1]->getName());
            }
            else if (hand[i - 1]->getName() == "spring")
            {
                setSeason(hand[i - 1]->getName());
            }
            else if (hand[i - 1]->getName() == "leader")
            {
                setIfLeader(true);
            }
            else if (hand[i - 1]->getName() == "horse")
            {
                setIfHorse(true);
            }
            else if (hand[i - 1]->getName() == "scarecrow")
            {
                setIfSscarecrow(true);
                usedCards.push_back(hand[i - 1]);
                hand.erase(hand.begin() + (i - 1));
                turn = false;

                return;
            }
            else if (hand[i - 1]->getName() == "dean")
            {
                setIfDean(true);
            }
            usedCards.push_back(hand[i - 1]);
            hand.erase(hand.begin() + (i - 1));
            turn = true;

            return;
        }
    }
}
void Player::updateYellowSpecialR(int x, int y, int cardWidth, int cardHeight, bool &turn)
{
    Vector2 mousePosition = GetMousePosition();
    for (int i = usedCards.size(); i > 0; i--)
    {
        std::string name = usedCards[i - 1]->getName();
        Rectangle cardRect = {static_cast<float>(x), static_cast<float>(y - 80 + (i - 1) * 25), static_cast<float>(cardWidth), static_cast<float>(cardHeight)};

        if (CheckCollisionPointRec(mousePosition, cardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            hand.push_back(usedCards[i - 1]);
            usedCards.erase(usedCards.begin() + (i - 1));
            turn = true;
            setIfSscarecrow(false);
            break;
        }
    }
}

void Player::updateCardsSpecialL(int x, int y, int cardWidth, int cardHeight, bool &turn)
{
    Vector2 mousePosition = GetMousePosition();

    for (size_t i = hand.size(); i > 0; i--)
    {
        std::string name = hand[i - 1]->getName();

        Rectangle cardRect = {static_cast<float>(x - 100), static_cast<float>(y + (i - 1) * 25), static_cast<float>(cardWidth), static_cast<float>(cardHeight)};

        if (CheckCollisionPointRec(mousePosition, cardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (hand[i - 1]->getName() == "winter")
            {
                setSeason(hand[i - 1]->getName());
            }
            else if (hand[i - 1]->getName() == "spring")
            {
                setSeason(hand[i - 1]->getName());
            }
            else if (hand[i - 1]->getName() == "leader")
            {
                setIfLeader(true);
            }
            else if (hand[i - 1]->getName() == "horse")
            {
                setIfHorse(true);
            }
            else if (hand[i - 1]->getName() == "scarecrow")
            {
                setIfSscarecrow(true);
                usedCards.push_back(hand[i - 1]);
                hand.erase(hand.begin() + (i - 1));
                turn = false;

                return;
            }
            else if (hand[i - 1]->getName() == "dean")
            {
                setIfDean(true);
            }
            usedCards.push_back(hand[i - 1]);
            hand.erase(hand.begin() + (i - 1));
            turn = true;

            return;
        }
    }
}
void Player::updateYellowSpecialL(int x, int y, int cardWidth, int cardHeight, bool &turn)
{
    Vector2 mousePosition = GetMousePosition();
    for (int i = usedCards.size(); i > 0; i--)
    {
        std::string name = usedCards[i - 1]->getName();
        Rectangle cardRect = {static_cast<float>(x - 100), static_cast<float>(y + (i - 1) * 25), static_cast<float>(cardWidth), static_cast<float>(cardHeight)};

        if (CheckCollisionPointRec(mousePosition, cardRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            hand.push_back(usedCards[i - 1]);
            usedCards.erase(usedCards.begin() + (i - 1));
            turn = true;
            setIfSscarecrow(false);
            break;
        }
    }
}
void Player::showSeason(Texture2D texture)
{
    Vector2 position = {498, 261};
    Rectangle destRec = {position.x, position.y, (float)texture.width, (float)texture.height};

    DrawTexture(texture, position.x, position.y, WHITE);
}

void Player::setIfSscarecrow(bool ifScarecrow)
{
    this->ifScarecrow = ifScarecrow;
}
bool Player::getIfScarecrow()
{
    return ifScarecrow;
}
std::vector<std::shared_ptr<Card>> Player::getUsedCards()
{
            return usedCards;
}
void Player::setIfDean( bool ifDean )
{
    this->ifDean = ifDean;
}
bool Player::getIfDean()
{
    return ifDean;
}
bool Player::operator== (const Player & other)
{
    return this->name == other.name;
}
