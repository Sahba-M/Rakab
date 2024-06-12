#include <iostream>

#include "purple.h"
#include "control.h"


class SpringCard :public PurpleCard
{
  public:
   virtual void setPriority() override;
   virtual void useCard ( std::vector <Player> players, int numPlayer = 0  ) override;
   friend std::vector<Player> Control::getPlayers();



  private:
};