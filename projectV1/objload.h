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
        Vertex parseVertex(std::string line);
        std::vector<float> static coordinateScanner(std::string line);
        void checkMin(Vertex v);
        void checkMax(Vertex v);
        std::vector<float> findCenter();
    private:
        std::string fileName;
        std::vector<Vertex> vertices;
        std::vector<face> facets;
        std::vector<Vertex> normals;
        std::vector<float> maxCoords;
        std::vector<float> minCoords;
        std::vector<float> center;
};

#endif // OBJLOAD_H
