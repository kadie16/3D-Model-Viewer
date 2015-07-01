#ifndef OBJLOAD_H
#define OBJLOAD_H
#include "vertex.h"
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
    //private:
        std::string fileName;
        std::vector<Vertex> vertices;


};

#endif // OBJLOAD_H
