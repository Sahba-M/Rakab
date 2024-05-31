#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

#ifndef MAP_H
#define MAP_H

class Map {
    public:
        void readMatrix ();
        void readUnorderedMap ();
        bool checkAdjacent ( const std::string & p1 , const std::string & p2 );

    private:
        std::vector < std::vector <int> > adjacencyMatrix ;
        std::unordered_map < std::string , int > provinceMap ;

};

#endif