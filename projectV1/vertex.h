#ifndef VERTEX_H
#define VERTEX_H
#include <string>
#include <sstream>
#include<iostream>

class Vertex
{
  public:
    Vertex(std::string input);
    void print();
    double getX();
    double getY();
    double getZ();
  private:
    double x,y,z;
};

#endif // VERTEX_H
