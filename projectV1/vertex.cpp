#include "vertex.h"

using namespace std;

Vertex::Vertex(string input)
{
    float vertexArr[3];
    sscanf(input.c_str(), "%*s %f %f %f", &vertexArr[0], &vertexArr[1], &vertexArr[2]);
    x = vertexArr[0];
    y = vertexArr[1];
    z = vertexArr[2];
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

void Vertex::print()
{
   cout << this -> x << " , " << this -> y << " , " << this -> z << endl;

}

