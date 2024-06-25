#include<vector>
#include <memory>

#include "card.h"
#include "player.h"

#ifndef CONTROL_H
#define CONTROL_H

class Control {
    
    public:
        Control(); 
        void setCards();//Filling vector cards
        void setPlayerNumber (int playerNumber);
        void controlNumber();//Players should be between 3 and 6
        void shuffleCards();
        void getInformation();
        void showColors();
        void distributeCards();
        void readProvinces();//Filling the provinces vector
        void showUncaptured();//Showing provinces that have not been captured at all
        void setWar();//
        void selectMove(Player & player,int index);//
        void showPlayGround();//
        void selectWarPlace (Player & player);//
        void setProvinceNumber(int provinceNumber);//
        void guideGame();//Show game guide
        void guideCards();//Display guide cards
        void cardAction();//
        void setSeason( std::string season );//
        void showPurpleCard();
        void run();//
        void setDeterminer( Player & Determiner);
        void setPlayersReady();//
        void burnCards();//
        void chargeCards();//
        void showAllCaptured();//
        void askBurn();//
        bool endEachWar();//
        bool winEachWar();//
        bool endGame();//
        int  getPlayerNumber();//
        int  findPlayerIndex ( const Player & player );//
        int  getProvinceNumber();//
        std::string controlColors();//
        std::vector<Player> getPlayers();//
        std::vector<Player> maxProvinces();//
        Player & getDeterminer();//
        Player & youngestPlayer();//

    private:
        std::vector<std::shared_ptr<Card>> cards;//A vector of all cards
        std::vector<std::shared_ptr<Card>> allBurnedCards;
        std::vector<std::string> provinces;
        std::vector<std::string> colors = {"RED", "YELLOW", "GREEN", "BLUE", "PURPLE", "PINK"};
        std::vector<std::string> move;
        std::vector<Player> players;
        std::vector<int> playersIndices;
        int playerNumber;//The number of players in the game
        int provinceNumber;
        std::string warPlace;
        std::string season;
        Player winner;
        Player DeterminerOfWar;//Determining the location of the battle
};

#endif