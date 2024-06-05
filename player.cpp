#include "player.h"
#include "card.h"

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
    this->age = age ;
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
void Player::addCard ( Card card )
{
    hand.push_back( card );
}
void Player::showHandCards ()
{
    for ( int i = 0 ; i < hand.size() ; i++ )
    {
        std::cout << hand[i].getName() << " --- " ;
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
int Player::getCardsEachPlayer()
{
    return (10 + capturedProvinces.size());
}
void Player::useCard ( Card card )
{
    bool found = false;
    do 
    {
        auto elementFound = std::find(hand.begin(), hand.end(), card);
        if (elementFound != hand.end())
        {
            hand.erase(elementFound);
            found = true;
            usedCards.push_back(card);
        }
        else
        {
            std::cout << " ERROR: Please Enter Valid Name For Card : " << std::endl;
            found = false;
        }
    } while (!found);
}