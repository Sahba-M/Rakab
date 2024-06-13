#include <iostream>
#include <algorithm>
#include <memory>
#include <typeinfo>

#include "player.h"
#include "card.h"
#include "purple.h"
#include "yellow.h"
#include "scarecrow.h"
#include "princes.h"


struct SharedPtrCompare {
    template <class T, class U>
    bool operator() ( const std::shared_ptr <T> & lhs , const std::shared_ptr <U> & rhs ) const 
    {
        return *lhs == *rhs;
    }
};

Player::Player(){ scorePlayer = 0 ; };
Player::Player ( int age , std::string name , std::string color ) 
{
  setAge( age );
  setName( name );
  setColor( color );
} 
void Player::setName ( std::string name )
{
    this->name = name ;
}
void Player::setAge ( int age )
{
    if (age > 0)
    {
        this->age = age ;
    } else
    {
        age = 0;
    }
}
void Player::setColor ( std::string color )
{
    this->color = color ;
}
int Player::getAge() const 
{
    return age ;
}
std::string Player::getName() const 
{
    return name ;
}
std::string Player::getColor() const 
{
    return color ;
}
void Player::addCard ( std::shared_ptr<Card> card )
{
    hand.push_back( card );
}
void Player::showHandCards ()
{
    for ( int i = 0 ; i < hand.size() ; i++ )
    {
        std::cout << hand[i]->getName() << " --- " ;
    }
    std::cout << std::endl;
}
void Player::addProvinces( std::string province )
{
    capturedProvinces.push_back(province);
}
void Player::showProvinces()
{
    for (int i = 0; i < capturedProvinces.size(); i++)
    {
        std::cout << capturedProvinces[i] << " ";
    }
    
}
int Player::getCardsEachPlayer()//The number of cards to be dealt
{
    return (10 + capturedProvinces.size());
}
void Player::selectCard()
{
    std::shared_ptr <Card> card;
    // recognizeYellow();
    std::string tempName;
    bool found = true;
    do
    {
        if ( found == true )
            std::cout  << " Enter Your Chosen Card: ";
        std::cin >> tempName;
       
        
        if ( tempName.length() <= 2)
            card = std::make_shared <YellowCard> (tempName);
        else
            card = std::make_shared <PurpleCard> (tempName);
        auto elementFound = std::find_if(hand.begin(), hand.end(), [ & card ]( const std::shared_ptr <Card> & c ) { return *c == *card ; });
        if ( tempName == "scarecrow" )
        { 
            if (yellowCards.size() == 0)
            {
                found = false; 
            } else
            {
                ScarecrowCard scarecrow ;
                scarecrow.useThisCard(*this);
            }
            
        }
        else if ( tempName == "spring" || tempName == "winter" )
            setSeason(tempName);
        if (elementFound != hand.end())
        {
            found = true;
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
std::string Player:: getSeason()
{
    return season;
}
void Player::showUsedCards()
{
    std::cout << getName() << " : ";
    if ( usedCards.size() > 0 )
    {
        for ( int i = 0 ; i < usedCards.size() ; i++ )
        {
            std::cout << usedCards[i]->getName() << " - ";
        }
    } 
    std::cout << std::endl;
}
void Player::recognizeYellow()
{
    yellowCards.resize(0);
    for (const auto &  usedCard : usedCards) 
     { 
           if (std::dynamic_pointer_cast<YellowCard>(usedCard)) 
           {
              yellowCards.push_back(usedCard);
           }
     }
}
bool Player::hasYelloCard()
{
    for(const auto & card : hand)
    {
        if (std::dynamic_pointer_cast<YellowCard>(card))
        {
            return false;
        } 
    }
    return true;
}

void Player::showYcard()
{
    //  recognizeYellow();
     for (const auto &  usedYcard : yellowCards) 
     {
        std::cout << usedYcard->getName() <<" --- ";
     }
} 
bool Player::isFind ( std::shared_ptr<Card> Ycard )//for finding yellow card
{
    auto elementFound = std::find_if(yellowCards.begin(), yellowCards.end(), [Ycard](const std::shared_ptr<Card> & card) { return *card == *Ycard; });
        if (elementFound != yellowCards.end())
        {
            hand.push_back(Ycard);
            usedCards.erase(std::remove(usedCards.begin(), usedCards.end(), *elementFound), usedCards.end());
            return true ;
        }
        else 
        {
            return false ;
        }
}
std::vector<std::shared_ptr<Card>> Player::getYcards()
{
    return yellowCards ;
}
void Player::setScorePlayer ( int scorePlayer )
{
    this -> scorePlayer = scorePlayer ;
}
int Player::getScorePlayer()
{
    return scorePlayer ;
}
int Player::maxYcards()
{    
    std::vector<int> yellowIntegers;
    for (auto card: yellowCards)
    {
        yellowIntegers.push_back(stoi(card->getName()));
    }
    auto maxElement = std::max_element(yellowIntegers.begin(), yellowIntegers.end());
    return (*maxElement);   
}
bool Player::hasDrummer()
{
    std::shared_ptr<Card> card = std::make_shared<PurpleCard>("drummer");
    auto elementFound = std::find ( usedCards.begin(), usedCards.end(), card );
    if ( elementFound != usedCards.end() )
    {
        return true ;
    }
    else
        return false ;
}
bool Player::hasPrinces()
{
   std::shared_ptr<Card> card = std::make_shared<PurpleCard>("princes");
   auto elemenFound = std::find (usedCards.begin(), usedCards.end(), card );
   if ( elemenFound != usedCards.end())
   {
     return true;
   } else
        return false;
}
int Player::numberOfPrinces()
{
    int counter = 0;
    
    for( auto card : usedCards)
    {
       if (typeid(*card) == typeid(PrincesCard))
       {
        counter++;
       }
    }
    return counter;  
}
int Player::getHandSize()
{
    return hand.size();
}
void Player::setPass( bool pass )
{
    this -> pass = pass;
}
bool Player::getPass()
{
    return pass;
}
void Player::yellowInScore()
{
    int sum = 0 ;
    recognizeYellow();
    for (auto card : yellowCards)
    {
        sum += stoi(card->getName());
    }
    scorePlayer = sum ;
}