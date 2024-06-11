#include<vector>
#include <memory>

#include "card.h"
#include "player.h"

#ifndef CONTROL_H
#define CONTROL_H

class Control {
    
    public:
        Control(); 
        void setCards();
        void setPlayerNumber (int playerNumber);
        int  getPlayerNumber();
        void controlNumber();
        void shuffleCards();
        void showCards();
        Player youngestPlayer();
        void getInformation();
        std::string controlColors();
        void showColors();
        void distributeCards ();
        void showPlayersHand();
        std::string chosenProvince(Player &player);
        void readProvinces();
        void showUncaptured();
        void test();
        void selectMove(Player & player);
        void showPlayGround();
        void selectWarPlace (Player & player);
        void setProvinceNumber(int provinceNumber);
        int  getProvinceNumber();
        

    private:
        std::vector<std::shared_ptr<Card>> cards;
        std::vector<Player> players;
        std::vector<std::string> provinces;
        std::vector<std::string> colors = {"RED", "YELLOW", "GREEN", "BLUE", "PURPLE", "PINK"};

        int playerNumber;
        int provinceNumber;
        std::string warPlace;
};

#endif