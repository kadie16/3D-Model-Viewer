#ifndef OBJLOAD_H
#define OBJLOAD_H
#include <iostream>
#include<fstream>
#include<vector>
#include<string>


class objLoad
{
    public:
        objLoad();
        objLoad(std::string fName);
        std::string getFileName(void);
    private:
        std::string fileName;


};

#endif // OBJLOAD_H
