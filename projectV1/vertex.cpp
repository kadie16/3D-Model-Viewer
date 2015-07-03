#include "vertex.h"

using namespace std;

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
    else if (type == 'f')
    {
        float vertexArr[3];
        sscanf(input.c_str(), "%*s %f/%f", &vertexArr[0], &vertexArr[1], &vertexArr[2]);
        x = vertexArr[0];
        y = vertexArr[1];
        z = vertexArr[2];

        //cout << this -> x << ' , ' << this -> y << ' , ' << this -> z << endl;
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

