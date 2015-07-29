#ifndef OBJ_H
#define OBJ_H
#include<CGAL/Modifier_base.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Polyhedron_3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include "vertex.h"
#include <QGLWidget>
#include <QTimer>
#include <QString>
#include "face.h"


template <class HDS>
class obj:public CGAL::Modifier_base<HDS>
{
public:
    obj(){};
    build(std::string fName);
    std::string getFileName();
    void print();
    std::vector<Vertex> getVertices();
    std::vector<face> getFacets();
    std::vector<Vertex> parseFace(std::string line);
    Vertex parseVertex(std::string line);
    std::vector<float> static coordinateScanner(std::string line);
    void checkMin(Vertex v);
    void checkMax(Vertex v);
    std::vector<float> getMaxCoords();
    std::vector<float> getMinCoords();
    std::vector<float> findCenter();
    float findRadius();
    CGAL::Polyhedron_incremental_builder_3<HDS> builder(hds, true);
private:
    std::string fileName;
    std::vector<Vertex> vertices;
    std::vector<face> facets;
    std::vector<Vertex> normals;
    std::vector<float> maxCoords;
    std::vector<float> minCoords;
    std::vector<float> center;
    float radius;
};

#endif // OBJ_H
