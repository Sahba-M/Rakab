#include <iostream>

#include "purple.h"


class DrummerCard:public PurpleCard
{
  
  public:
   DrummerCard();
   virtual void setPriority() override;
   virtual void useCard ( std::vector <Player> players, int numPlayer ) override;




  private:
   
};