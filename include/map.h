#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

#ifndef MAP_H
#define MAP_H

class Map {
    public:
        void readMatrix ();//Filling the Vector of adjacencies (0,1)
        void readUnorderedMap ();//Filling the unordermap
        bool checkAdjacent ( const std::string & p1 , const std::string & p2 );//Check the adjacencies

    private:
        std::vector < std::vector <int> > adjacencyMatrix ;//2D vector of adjacencies (0,1)
        std::unordered_map < std::string , int > provinceMap ;

};
#endif