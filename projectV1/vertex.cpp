#include "vertex.h"

using namespace std;

Vertex::Vertex(string input)
{
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

void Vertex::print()
{
   //cout << this.x << " , " << this.y << " , " << this.z << endl;

}

