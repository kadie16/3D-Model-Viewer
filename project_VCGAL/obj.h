#ifndef OBJ_H
#define OBJ_H

#include<CGAL/Modifier_base.h>
#include<CGAL/Polyhedron_3.h>
#include <CGAL/HalfedgeDS_default.h>

template <class HDS>
class obj : public CGAL::Modifier_base<HDS>{
public:
    typedef CGAL::Polyhedron_3<HDS> Polyhedron;
    typename CGAL::Polyhedron_3<HDS>::Vertex vertex;

    obj();
    void build(std::string fName);
    std::string getFileName();
    void print();
    typename Polyhedron::Vertex_iterator getVertices();
    typename Polyhedron::Facet_iterator getFacets();
    std::vector<int> parseFace(std::string line);
    vertex parseVertex(std::string line);
    std::vector<float> static coordinateScanner(std::string line);
    void checkMin(vertex v);
    void checkMax(vertex v);
    std::vector<float> getMaxCoords();
    std::vector<float> getMinCoords();
    std::vector<float> findCenter();
    float findRadius();

private:
    std::string fileName;
    std::vector<vertex> normals;
    std::vector<float> maxCoords;
    std::vector<float> minCoords;
    std::vector<float> center;
    float radius;

    CGAL::Polyhedron_incremental_builder_3<HDS> builder();
    Polyhedron poly();
};

#endif // OBJ_H
