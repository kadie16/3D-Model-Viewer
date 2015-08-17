#include "errors.h"
#include <iostream>

void fatalError(std::string errorString)
{
    std::cout << "ERROR: " << errorString << std::endl;
    //std::cout << "Press any key to quit" << std::endl;
    //int temp;
   // std::cin >> temp;
    std::terminate();
}
