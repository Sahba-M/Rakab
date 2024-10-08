#include "map.h"

void Map::readMatrix ()
{
    std::ifstream input ("../src/matrix.txt") ; 
    if (!input.is_open()) 
        std::cerr << " Unable to open file ! " << std::endl ;

    int number;
    while (!input.eof()) 
    {
        std::vector <int> row ;
        for ( int i = 0 ; i < 15 ; i++ ) 
        {
            if ( input >> number )   
            {
                row.push_back(number);
            }
        }
        if (!row.empty()) 
        {
            adjacencyMatrix.push_back(row);
        }
    }
    input.close();  
}
void Map::readUnorderedMap ()
{
    std::ifstream input ; 
    input.open("../src/map.txt") ;
    if (!input.is_open()) 
        std::cerr << " Unable to open file !" << std::endl ;
        
    std::string key ; // The names of the provinces
    int value ; // Number of provinces
    while (!input.eof())
    {
        if ( input >> value >> key )
        {
            provinceMap[key] = value ;
        }
    }
    input.close();
}
bool Map::checkAdjacent ( const std::string & p1 , const std::string & p2 )
{
    int index1 = provinceMap[p1];
    int index2 = provinceMap[p2];

    if (adjacencyMatrix[index1][index2] == 1)
        return true;
    else  
        return false;  
}