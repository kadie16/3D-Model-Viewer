#ifndef FACE_H
#define FACE_H
#include <string>
#include "vertex.h"
#include <vector>
#include <string>
class face
{
public:
    face();
    face(Vertex first, Vertex second, Vertex third);
    face(std::string line);
    Vertex getVertex(unsigned number);
    std::vector<float> getNormal();
    bool hasNormal();
    void findNormal();
    void print();

private:
    Vertex v1;
    Vertex v2;
    Vertex v3;
    std::vector<float> normal;
};

#endif // FACE_H
