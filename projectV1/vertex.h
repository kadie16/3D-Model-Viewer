#ifndef VERTEX_H
#define VERTEX_H
#include <string>

class Vertex
{
  public:
    Vertex();
    Vertex(std::string input);
    getX();
    getY();
    getZ();
  private:
    double x,y,z;
};

#endif // VERTEX_H
