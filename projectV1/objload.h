#ifndef OBJLOAD_H
#define OBJLOAD_H
#include <iostream>
#include<fstream>
#include <sstream>
#include<vector>
#include<string>
#include<iterator>
#include "vertex.h"
#include <QGLWidget>
#include <QTimer>
#include <QString>


class objLoad
{
    public:
        objLoad();
        objLoad(std::string fName);
        std::string getFileName(void);
        void print();
        std::vector<Vertex> getVertices();
        std::vector<Vertex> getFacets();
    //private:
        std::string fileName;
        std::vector<Vertex> vertices;
        std::vector<Vertex> facets;


};

#endif // OBJLOAD_H
