#ifndef OBJLOAD_H
#define OBJLOAD_H
#include <iostream>
#include<fstream>
#include <sstream>
#include<vector>
#include<string>
#include<iterator>
#include <QGLWidget>
#include <QTimer>
#include <QString>
#include<CGAL/Modifier_base.h>
#include<CGAL/Polyhedron_3.h>
#include<CGAL/Polyhedron_incremental_builder_3.h>

typedef double Real;
typedef CGAL::Simple_cartesian<Real> Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Polyhedron::HalfedgeDS HalfedgeDS;

template <class HDS>
class objLoad : public CGAL::Modifier_base<HDS>
{
    public:
        typedef typename HDS::Vertex Vertex;
        typedef typename Vertex::Point Point;
        /* Constructors */
        objLoad() { }
        objLoad(std::string Path);
        /* Functor */
        void operator()(HDS& hds);
        /* Path Functions */
        void setFilePath(string Path);
        std::string getPath();
        /* Parsing */
        std::vector<int> parseFace(std::string line);
        typename Polyhedron::Vertex parseVertex(std::string line);
        std::vector<float> static coordinateScanner(std::string line);
        /* Determine Model Dimensions */
        void checkMin(typename Polyhedron::Vertex v);
        void checkMax(typename Polyhedron::Vertex v);
        std::vector<float> getMaxCoords();
        std::vector<float> getMinCoords();
        std::vector<float> findCenter();
        float findRadius();
    private:
        std::string path;
        std::vector<float> maxCoords;
        std::vector<float> minCoords;
        std::vector<float> center;
        float radius;
};

#endif // OBJLOAD_H
