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
    model(objLoad<HDS> objFile);
    void computeNormals();
    Polyhedron poly();
    void drawMe();
    void drawTriangle(Polyhedron::Facet_const_handle f);
    bool generateVolumeMesh();
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
private:
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
};

#endif // MODEL_H
