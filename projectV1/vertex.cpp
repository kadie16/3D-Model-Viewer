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
       int tokenCount;
       input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
       input.erase(0,1);
       string delimiter = "/";
       size_t pos = 0;
       string token;



       while ((pos = input.find(delimiter) != string::npos))
       {
        token = input.substr(0, input.find(delimiter));
        cout << token << endl;
        input.erase(0, pos + delimiter.length());
       }
        /*x = vertexArr[0];
        y = vertexArr[1];
        z = vertexArr[2];*/
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

