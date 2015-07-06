#ifndef VERTEX_H
#define VERTEX_H
#include <string>
#include <sstream>
#include<iostream>

class Vertex
{
private:
  double x,y,z;

public:
    Vertex();
    Vertex(std::string input, char type);
    void print();
    double getX();
    double getY();
    double getZ();

};

#endif // VERTEX_H
