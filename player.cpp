#include <iostream>
#include <algorithm>
#include <memory>

#include "player.h"
#include "card.h"
#include "purple.h"
#include "yellow.h"
#include "scarecrow.h"


struct SharedPtrCompare {
    template <class T, class U>
    bool operator() ( const std::shared_ptr <T> & lhs , const std::shared_ptr <U> & rhs ) const 
    {
        return *lhs == *rhs;
    }
};

Player::Player(){};
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
    std::string *tempNamePtr = nullptr;
    std::string tempName;
    bool found = true;
    do
    {
        // system("cls");
        if ( found == true )
            std::cout  << " Enter Your Chosen Card: ";
        std::cin >> tempName;
        tempNamePtr = &tempName;
        
        if ( std::dynamic_pointer_cast <YellowCard>(tempName))
             card = std::make_shared <YellowCard> (tempName);
        else
            card = std::make_shared <PurpleCard> (tempName);
        auto elementFound = std::find_if(hand.begin(), hand.end(), [ & card ]( const std::shared_ptr <Card> & c ) { return *c == *card ; });
        if ( tempName == "scarecrow" )
        {
            ScarecrowCard scarecrow ;
            scarecrow.useCard(*this);
        }
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
void Player::showYcard()
{
   for (const auto&  usedCard : usedCards) 
   { 
         if (std::dynamic_pointer_cast<YellowCard>(usedCard)) 
         {
             yellowCards.push_back(usedCard);
         }
   }
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
            usedCards.erase(elementFound);
            // showYcard();
            return true ;
        }
        else 
        {
            return false ;
        }
}