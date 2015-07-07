#include "vertex.h"

using namespace std;

Vertex::Vertex()
{

}

Vertex::Vertex(string input, char type)
{
    if (type == 'v')
    {
        float vertexArr[3];
        sscanf(input.c_str(), "%*s %f %f %f", &vertexArr[0], &vertexArr[1], &vertexArr[2]);
        x = vertexArr[0];
        y = vertexArr[1];
        z = vertexArr[2];
    }
    else if (type == 'n')
    {
        float vertexArr[3];
                sscanf(input.c_str(), "%*s %f %f %f", &vertexArr[0], &vertexArr[1], &vertexArr[2]);
        x = vertexArr[0];
        y = vertexArr[1];
        z = vertexArr[2];
    }
    else if (type == 'f')
    {
        float vertexArr[6];
        sscanf(input.c_str(), "%*s %f/%f %f/%f %f/%f", &vertexArr[0], &vertexArr[1], &vertexArr[2], &vertexArr[3], &vertexArr[4], &vertexArr[5]);
        x = vertexArr[0];
        y = vertexArr[2];
        z = vertexArr[4];
    }
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

