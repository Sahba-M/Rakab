#include<vector>

#include "card.h"
#include "player.h"

#ifndef CONTROL_H
#define CONTROL_H

class Control {
    
    public:
        Control(); 
        void setCards();
        void setPlayerNumber(int playerNumber);
        int  getPlayerNumber();
        void controlNumber();
        void shuffleCards();
        void showCards();
        void Control::youngestPlayer();

    private:
        std::vector<Card> cards;
        int playerNumber;
};

#endif