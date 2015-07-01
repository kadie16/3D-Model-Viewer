#include "vertex.h"
using namespace std;

Vertex::Vertex()
{
    double x,y,z;
}

Vertex::Vertex(string input)
{
    double x,y,z;
    stringstream inStream(input);
    inStream >> x;
    inStream >> y;
    inStream >> z;
}

double Vertex::getX()
{
    return x;
}

double Vertex::getY()
{
    return y;
}

double Vertex::getZ()
{
    return z;
}

