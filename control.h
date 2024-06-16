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
        void controlNumber();
        void shuffleCards();
        void getInformation();
        void showColors();
        void distributeCards();
        void readProvinces();
        void showUncaptured();
        void setWar();
        void selectMove(Player & player,int index);
        void showPlayGround();
        void selectWarPlace (Player & player);
        void setProvinceNumber(int provinceNumber);
        void guideGame();
        void guideCards();
        void cardAction();
        void setSeason( std::string season );
        void showPurpleCard();
        void run();
        void setDeterminer( Player & Determiner);
        void setPlayersReady();
        void burnCards();
        void chargeCards();
        void showAllCaptured();
        void askBurn();
        bool endEachWar();
        bool winEachWar();
        bool endGame();
        int  getPlayerNumber();
        int findPlayerIndex ( const Player & player );
        int  getProvinceNumber();
        std::string controlColors();
        std::vector<Player> getPlayers();
        std::vector<Player> maxProvinces();
        Player & getDeterminer();
        Player & youngestPlayer();



    private:
        std::vector<std::shared_ptr<Card>> cards;
        std::vector<std::shared_ptr<Card>> allBurnedCards;
        std::vector<std::string> provinces;
        std::vector<std::string> colors = {"RED", "YELLOW", "GREEN", "BLUE", "PURPLE", "PINK"};
        std::vector<std::string> move;
        std::vector<Player> players;
        std::vector<int> playersIndices;

        int playerNumber;
        int provinceNumber;
        std::string warPlace;
        std::string season;
        Player winner;
        Player DeterminerOfWar;
};

#endif