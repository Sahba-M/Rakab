#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>
#include "raylib.h"
#include "asset.h"


class Card { //The card class is a parent class

     friend std::istream & operator>> ( std::istream & input , std::shared_ptr<Card> & card );
     friend std::ostream & operator<< ( std::ostream & output , const Card & card );

   
    public:
        Card ( std::string name );
        Card();
        virtual ~Card();
        void setName(std::string name);
        std::string getName();
        bool operator== (const Card & other);
        virtual void draw ( int x , int y , AssetManager & myAsset ){};
        // AssetManager myAsset;

  
    protected:
        std::string name;
};
#endif 

