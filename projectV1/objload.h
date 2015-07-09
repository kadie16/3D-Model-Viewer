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
#include "face.h"


class objLoad
{
    public:
        objLoad();
        objLoad(std::string fName);
        std::string getFileName();
        void print();
        std::vector<Vertex> getVertices();
        std::vector<face> getFacets();
        std::vector<Vertex> parseFace(std::string line);
    private:
        std::string fileName;
        std::vector<Vertex> vertices;
        std::vector<face> facets;
        std::vector<Vertex> normals;
};

#endif // OBJLOAD_H
