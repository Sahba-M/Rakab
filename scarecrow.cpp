#include<iostream>


#include "purple.h"
#include"scarecrow.h"

void ScarecrowCard::useCard(Player &player)
{
   bool found = false;
    std::string selectYcard;
    std::cout << "\n Which Card Do You Want To Remove? : ";
    showUncaptured();
    do
    {
        system("cls");
        std::cout << "\n\n " << player.getName() << " Enter Your Chosen selectYcard To War : ";
        std::cin >> selectYcard;

        auto elementFound = std::find(selectYcards.begin(), selectYcards.end(), selectYcard);
        if (elementFound != selectYcards.end())
        {
            selectYcards.erase(elementFound);
            found = true;
            break;
        }
        else
        {
            std::cout << " ERROR: Please Enter Your Desired selectYcard Again : " << std::endl;
            found = false;
        }
    } while (!found);
    return selectYcard;
}