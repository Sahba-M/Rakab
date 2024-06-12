#include <iostream>

#include "purple.h"
#include "control.h"


class SpringCard :public PurpleCard
{
  public:
   virtual void setPriority() override;
   virtual void useCard ( std::vector <Player> players, int numPlayer ) override;
   friend std::vector<Player> Control::getPlayers();
   int findMaxScore ( std::vector <Player> players );
   std::vector<int> findMaxPlayer ( std::vector <Player> players );
   
   

  private:
};