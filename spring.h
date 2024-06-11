#include <iostream>

#include "purple.h"

class SpringCard :public PurpleCard
{
  public:
   virtual void setPriority() override;
   virtual void useCard ( Player & player ) override;



  private:
};