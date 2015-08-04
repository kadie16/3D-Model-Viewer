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
#include<CGAL/HalfedgeDS_default.h>
#include<CGAL/Simple_cartesian.h>
#include<CGAL/Modifier_base.h>
#include<CGAL/Polyhedron_3.h>
#include<CGAL/Polyhedron_incremental_builder_3.h>

/*********************************************************************************/
/**************************** My Items ******************************************/
/*******************************************************************************/

struct Facet_normal {
    template <class Facet>
    void operator()( Facet& f) {
        typename Facet::Halfedge_handle h = f.halfedge();
        typename Facet::Normal_3 normal = CGAL::normal(h->next()->vertex()->point(),
                                                       h->vertex()->point(),
                                                       h->prev()->vertex()->point());
        f.normal() = normal / std::sqrt( normal * normal);
    }
};

struct Vertex_normal {
    template <class Vertex>
    void operator()( Vertex& v) {
        typename Vertex::Normal_3 normal = CGAL::NULL_VECTOR;
        typedef typename Vertex::Halfedge_around_vertex_const_circulator Circ;
        Circ c = v.vertex_begin();
        Circ d = c;
        CGAL_For_all( c, d) {
            if ( ! c->is_border())
                normal = normal + c->facet()->normal();
        }
        v.normal() = normal / std::sqrt( normal * normal);
    }
};

// A redefined items class for the Polyhedron_3 with a refined vertex
// class that contains a member for the normal vector and a refined
// facet with a normal vector instead of the plane equation (this is
// an alternative solution instead of using Polyhedron_traits_with_normals_3).

template <class Refs, class T, class P, class Norm>
class My_vertex : public CGAL::HalfedgeDS_vertex_base<Refs, T, P> {
    Norm  norm;
public:
    My_vertex() {} // repeat mandatory constructors
    My_vertex( const P& pt) : CGAL::HalfedgeDS_vertex_base<Refs, T, P>(pt) {}
    typedef Norm Normal_3;
    Normal_3&       normal()       { return norm; }
    const Normal_3& normal() const { return norm; }
};

template <class Refs, class T, class Norm>
class My_facet : public CGAL::HalfedgeDS_face_base<Refs, T> {
    Norm  norm;
public:
    // no constructors to repeat, since only default constructor mandatory
    typedef Norm Normal_3;
    Normal_3&       normal()       { return norm; }
    const Normal_3& normal() const { return norm; }
};

struct My_items : public CGAL::Polyhedron_items_3 {
    template <class Refs, class Traits>
    struct Vertex_wrapper {
        typedef typename Traits::Point_3  Point;
        typedef typename Traits::Vector_3 Normal;
        typedef My_vertex<Refs, CGAL::Tag_true, Point, Normal> Vertex;
    };
    template <class Refs, class Traits>
    struct Face_wrapper {
        typedef typename Traits::Vector_3 Normal;
        typedef My_facet<Refs, CGAL::Tag_true, Normal> Face;
    };
};


typedef double Real;
typedef CGAL::Simple_cartesian<Real> Kernel;
typedef CGAL::Polyhedron_3<Kernel, My_items> Polyhedron;
typedef Polyhedron::HalfedgeDS HalfedgeDS;
using namespace std;
template <class HDS>

/********************************************************************************/
/*********************************** OBJ LOAD **********************************/
/******************************************************************************/

class objLoad : public CGAL::Modifier_base<HDS>
{
    public:
        typedef typename HDS::Vertex Vertex;
        typedef typename Vertex::Point Point;
        /****************** Constructors ******************/
        objLoad(){}
        objLoad(std::string Path) {
            path = Path;
        }
        /****************** Functor ******************/
        void operator()(HDS &hds) {
            /* Empty Mesh */
            hds.clear();
            CGAL::Polyhedron_incremental_builder_3<HDS> builder(hds, true);
            builder.begin_surface(0,0);
            maxCoords.assign(3, 0);
            minCoords.assign(3,0);
            center.assign(3,0);
            /* Open File */
            cout << "Loading object from path:  " << path << endl;
            ifstream stream(path.c_str());
            if (stream.is_open()) {
                string currLine;
                while (!stream.eof()) {
                    /* Get next line of file */
                    getline(stream, currLine);
                    if (currLine.size() > 2) {
                        /* Determine whether it is a vertex, normal, or face line */
                        if (currLine[0] == 'v' && currLine[1] == ' ') {
                            Point newV = this->parseVertex(currLine);
                            builder.add_vertex(newV);
                            this->checkMax(newV);
                            this->checkMin(newV);
                         } else if (currLine[0] == 'v' && currLine[1] == 'n') {
                           /* Not Storing Normals */
                        } else if (currLine[0] == 'f' && currLine[1] == ' ') {
                            builder.begin_facet();
                            vector<float> v = this->parseFace(currLine);
                            builder.add_vertex_to_facet(v.at(0) - 1);
                            builder.add_vertex_to_facet(v.at(1) - 1);
                            builder.add_vertex_to_facet(v.at(2) - 1);
                            if (v.size() > 3)
                                builder.add_vertex_to_facet(v.at(3));
                            builder.end_facet();
                        }
                    }
                }
                builder.end_surface();
                stream.close();
            } else {
                cout << "File load failed!" << endl;
            }
        }
        /****************** Path Functions ******************/
        void setFilePath(std::string Path) {
            path = Path;
        }
        std::string getPath();
        /******************* Parsing *******************/
        std::vector<float> parseFace(std::string input) {
            vector<float> toReturn;
            /* Parses differently, depending on if there are slashes in line */
            if (input.find("/") != string::npos) {
                /* remove the "f" in front of the line */
                input.erase(0,1);
                string delimiter = "/";
                size_t pos = 0;
                string token;
                string token2;
                int index;
                int prevIndex = 0;
                while ((pos = input.find(delimiter) != string::npos)) {
                 /* Token is index of vertex in the face */
                 token = input.substr(0, input.find(delimiter));
                 istringstream(token) >> index; /* Only succeeds if token is an integer */
                 if (index != prevIndex){
                    toReturn.push_back(index);
                    prevIndex = index;
                }
                 /* Tossing out token2 until further notice */
                 token2 = input.substr(input.find(delimiter), input.find(' '));
                 /* Erases everything up until next index */
                 input.erase(0, token.length() + token2.length());
                }
            } else {
                /* If there aren't any slashes, parses like coordinates */
                return coordinateScanner(input);
            }
            return toReturn;
        }
        typename Vertex::Point parseVertex(std::string line) {
            vector<float> coords = coordinateScanner(line);
            Point newVertex(coords.at(0), coords.at(1), coords.at(2));
            return newVertex;
        }
        std::vector<float> static coordinateScanner(std::string line) {
            vector<float> toReturn;
            float vertexArr[3];
            sscanf(line.c_str(), "%*s %f %f %f", &vertexArr[0], &vertexArr[1], &vertexArr[2]);
            toReturn.push_back(vertexArr[0]);
            toReturn.push_back(vertexArr[1]);
            toReturn.push_back(vertexArr[2]);
            return toReturn;
        }
        /******************* Determine Model Dimensions *******************/
        void checkMin(Point v) {
            float x,y,z;
            x = v.hx();
            y = v.hy();
            z = v.hz();
            if (x < minCoords.at(0))
                minCoords[0] = x;
            if (y < minCoords.at(1))
                minCoords[1] = y;
            if (z < minCoords.at(2))
                minCoords[2] = z;
        }
        void checkMax(Point v) {
            float x,y,z;
            x = v.hx();
            y = v.hy();
            z = v.hz();
            if (x > maxCoords.at(0))
                maxCoords[0] = x;
            if (y > maxCoords.at(1))
                maxCoords[1] = y;
            if (z > maxCoords.at(2))
                maxCoords[2] = z;
        }

        std::vector<float> getMaxCoords() {
            return maxCoords;
        }
        std::vector<float> getMinCoords() {
            return minCoords;
        }
        std::vector<float> findCenter() {
            center[0] = (minCoords.at(0) + maxCoords.at(0))/2;
            center[1] = (minCoords.at(1) + maxCoords.at(1))/2;
            center[2] = (minCoords.at(2) + maxCoords.at(2))/2;
            return center;
        }
        float findRadius() {
            radius = sqrt((maxCoords.at(0) - center.at(0))*(maxCoords.at(0) - center.at(0))
                          +(maxCoords.at(1) - center.at(1))*(maxCoords.at(1) - center.at(1))
                          +(maxCoords.at(2) - center.at(2))*(maxCoords.at(2) - center.at(2)));
            return (radius);
        }

    private:
        std::string path;
        std::vector<float> maxCoords;
        std::vector<float> minCoords;
        std::vector<float> center;
        float radius;
};

#endif // OBJLOAD_H
