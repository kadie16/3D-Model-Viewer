#ifndef MODEL_H
#define MODEL_H
#include <QQuaternion>
#include "myitems.h"
#include "objload.h"
typedef Polyhedron::HalfedgeDS HDS;
class model
{
public:
    model();
    ~model();
    model(objLoad<HDS> objFile);
    void computeNormals();
    Polyhedron poly();
    void drawMe();
    void drawTriangle(Polyhedron::Facet_const_handle f);
    bool generateVolumeMesh();
    void drawVolume();
    void drawTriangle(Point p1, Point p2, Point p3);
    std::vector<float> center();
    float radius();
    std::vector<float> max();
    std::vector<float> min();
    float getTransX();
    float getTransY();
    void setTransX(float f);
    void setTransY(float f);
    void translate(float xT, float yT);
    void moveToCenter();
    void genBuffers();
    static int CheckGLErrors();
private:
    bool hasVolume;
    GLuint _vboID;
    objLoad<HDS> *objPtr = 0;
    Polyhedron polyhedron;
    Mesh_Polyhedron mesh;
    QQuaternion currQ;
    C3T3 c3t3;
    Tr t;
    float m_radius;
    double red,green,blue;
    std::vector<float> m_center;
    std::vector<float> maxCoords;
    std::vector<float> minCoords;
    std::vector<float> currTrans;
    int numFaces;
};

#endif // MODEL_H
