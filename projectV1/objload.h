#ifndef OBJLOAD_H
#define OBJLOAD_H
#include <iostream>
#include<fstream>
#include <sstream>
#include<vector>
#include<string>
#include<iterator>

class objLoad
{
    public:
        objLoad();
        objLoad(std::string fName);
        std::string getFileName(void);
        void print();
    //private:
        std::string fileName;
        std::vector<double> vertices;
        std::vector<int> facets;


};

#endif // OBJLOAD_H
