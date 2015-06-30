#ifndef OBJLOAD_H
#define OBJLOAD_H
#include <iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

class objLoad
{
    public:
        objLoad();
        objLoad(string fName);
        string getFileName(void);
    private:
        string fileName;
        vector<Vertex> vertices;

};

struct Vertex
{
    double x,y,z;
};

#endif // OBJLOAD_H
