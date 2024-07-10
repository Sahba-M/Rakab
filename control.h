#include<vector>
#include <memory>

#include "card.h"
#include "player.h"

#ifndef CONTROL_H
#define CONTROL_H

class Control {
    
    public:
        Control(); 
        void setCards(); //Filling vector cards
        void setPlayerNumber ( int playerNumber );
        void controlNumber(); //Players should be between 3 and 6
        void shuffleCards();
        void getInformation();
        void showColors();
        void distributeCards();
        void readProvinces(); //Filling the provinces vector
        void showUncaptured(); //Showing provinces that have not been captured at all
        void setWar();
        void setPeace( std::string peacePlace );
        void setWarPlace ( std::string warPlace );
        void selectMove ( Player & player,int index );
        void showPlayGround(); //Show used player cards
        void selectWarPlace ( Player & player );
        void setProvinceNumber ( int provinceNumber ); //Set the number of game provinces
        void guideGame(); //Show game guide
        void guideCards(); //Display guide cards
        void cardAction(); //calculate scores and special cards operation
        void setSeason ( std::string season );
        void showPurpleCard();
        void run();
        void setDeterminer ( Player & Determiner);
        void setDeterminerPeace ( Player & Determiner);
        void setPlayersReady(); //change to false variable of pass after each round (for all players)
        void burnCards(); //fill the allBurnedCards vector
        void chargeCards();
        void selectPeacePlace(Player &player);
        void showAllCaptured();
        void askBurn(); //to burn hand cards of the player who has not got yellow cards
        bool changeDeterminer(); 
        bool winGame(Player player);
        bool endEachWar(); //checking that all players pass
        bool winEachWar();
        bool endGame();
        int  levenshteinDistance(const std::string &s1, const std::string &s2); // Optimized function to calculate the Levenshtein distance between two strings
        int  controlAge();
        int  getPlayerNumber();
        int  findPlayerIndex ( const Player & player ); //finding the index of determiner to start a new round (for clockwise movement)
        int  getProvinceNumber();
        int  findMaxVirago(); // finding the max number of virago card in playground cards
        std::string controlColors();
        std::string getWarPlace();
        std::string getWarPeace();
        std::string findClosestMatch(const std::string &input, const std::vector<std::string> &cards, int threshold);

        std::vector<Player> getPlayers();
        std::vector<Player> maxProvinces(); //Find the players who have captured the most provinces
        std::vector<int> findIndexVirago(); //Find the indices of players who have the most virago card
        Player & getDeterminer();
        Player & getDeterminerPeace();
        Player & youngestPlayer();
        Player findLastDean(); //Find the last player who played dean
        
    
    private:
        std::vector<std::shared_ptr<Card>> cards; //A vector of all cards
        std::vector<std::shared_ptr<Card>> allBurnedCards;
        std::vector<std::string> provinces;
        std::vector<std::string> colors = {"RED", "YELLOW", "GREEN", "BLUE", "PURPLE", "PINK"};
        std::vector<std::string> cardsAndOrdersNames = {"drummer", "princes", "scarecrow", "spring", "winter", "help", "card", "pass"};

        std::vector<std::string> move; // for save move choices of players
        std::vector<Player> players;
        std::vector<int> playersIndices; // for saving indexes of players who pass
        int playerNumber; //The number of players in the game
        int provinceNumber;
        int threshold;
        std::string warPlace;
        std::string peacePlace = "null";
        std::string season;
        Player winner; // for winner of each round
        Player DeterminerOfWar; //Determining the location of the battle
        Player DeterminerOfPeace; //Determining the location of the peace place
        
};

#endif