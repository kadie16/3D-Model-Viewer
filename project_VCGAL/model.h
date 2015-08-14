#ifndef MODEL_H
#define MODEL_H
#include "objload.h"
#include <QQuaternion>

typedef Polyhedron::HalfedgeDS HDS;
class model
{
public:
    model();
    model(objLoad<HDS> objFile);
    void computeNormals();
    Polyhedron poly();
private:
    objLoad<HDS> *objPtr = 0;
    Polyhedron polyhedron;
    Mesh_Polyhedron mesh;
    QQuaternion currQ;
    C3T3 c3t3;
    Tr t;
    float radius;
    double red,green,blue;
    std::vector<float> center;
    std::vector<float> maxCoords;
    std::vector<float> minCoords;
};

#endif // MODEL_H
