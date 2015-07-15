#ifndef VERTEX_H
#define VERTEX_H
#include <string>
#include <sstream>
#include<iostream>
#include <cmath>
#include <vector>
class Vertex
{
private:
  float x,y,z;
  std::vector<float> normal;
  bool isInitialized;

public:
    Vertex();
    Vertex(float inX, float inY, float inZ);
    Vertex(std::string input, char type);
    void print();
    void parseCoordinates(std::string input);
    bool exists();
    float getX();
    float getY();
    float getZ();
    static float checkAngle(float va[], float vb[]);
    float * toArray();
    bool hasNormal();
    void assignNormal(float v1, float v2, float v3);
    std::vector<float> findNormal(Vertex v2, Vertex v3);
    void inheritNormal(Vertex parent);
    std::vector<float> getNormal();
    bool equalsVertex(Vertex v);
};

#endif // VERTEX_H
