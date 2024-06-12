#include<iostream>

#include "purple.h"

class Winter:public PurpleCard
{
  public:
   virtual void setPriority() override;
   virtual void useCard ( std::vector <Player> players, int numPlayer ) override;


  private:

};