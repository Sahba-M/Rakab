#include <string>

#ifndef CARD_H
#define CARD_H


class Card {
    friend std::istream & operator>> (std::istream & , Card &);

    public:
    Card( std::string name , int score = 0 );
    Card();
    void setScore(int score);
    void setName(std::string name);
    int getScore();
    std::string getName();
    bool operator== (const Card & other);
    // virtual void use() = 0 ;

    private:
    int score;
    std::string name;
};

#endif 

