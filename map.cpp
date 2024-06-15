#include "map.h"

void Map::readMatrix ()
{
    std::ifstream input ("matrix.txt") ; 
    if (!input.is_open()) 
        std::cerr << " Unable to open file ! " << std::endl ;
    int number;
    while (!input.eof()) 
    {

        std::vector <int> row ;
        for ( int i = 0 ; i < 14 ; i++ ) 
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
    input.open("map.txt") ;
    if (!input.is_open()) 
        std::cerr << " Unable to open file !" << std::endl ;
        
    std::string key ;
    int value ;
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
// int main()
// {
//     Map map ;
//     map.readUnorderedMap();
//     map.readMatrix();
//     std::cout << map.provinceMap["LIA"] << std::endl;
//     std::cout << map.provinceMap["ROLLO"] << std::endl;
//     std::cout << map.provinceMap["ENNA"] << std::endl;
//     std::cout << map.provinceMap.size() << std::endl;
//     std::cout << map.adjacencyMatrix.size() << std::endl;
//     std::cout << map.adjacencyMatrix[map.adjacencyMatrix.size()-1].size() << std::endl;

//     std::cout << map.checkAdjacent("LIA" , "ROLLO");
//     std::cout << " " ;
//     std::cout << map.checkAdjacent("ENNA" , "ROLLO");
// }