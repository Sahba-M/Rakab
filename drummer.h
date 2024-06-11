#include <iostream>

#include "purple.h"


class DrummerCard:public PurpleCard
{
  
  public:
   DrummerCard();
   virtual void setPriority() override;
   virtual void useCard ( Player & player ) override;




  private:
   
};