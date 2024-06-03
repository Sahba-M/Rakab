#include "player.h"

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