#include "vertex.h"

using namespace std;

Vertex::Vertex()
{

}

Vertex::Vertex(string input, char type)
{
    if (type == 'v' || type == 'n')
    {
        this->parseCoordinates(input);
    }
    else if (type == 'f')
    {
        if (input.find("/") != string::npos)
        {
            this->parseFace(input);
        } else {
          this->parseCoordinates(input);
        }
    }

}

void Vertex::parseFace(string input){
    int tokenCount;
    input.erase(0,1); // delete the f
    string delimiter = "/";
    size_t pos = 0;
    string token;
    string token2;
    int vertexArr[9];
    while ((pos = input.find(delimiter) != string::npos))
    {
     token = input.substr(0, input.find(delimiter)); // token indicates index of vertex
     istringstream(token) >> vertexArr[tokenCount];
     tokenCount ++; //count index tokens
     token2 = input.substr(input.find(delimiter), input.find(' ')); //tossing token2 for now
     input.erase(0, token.length() + token2.length());

    } // TODO: FIX THISS!!!!!!!!

     x = vertexArr[0];
     y = vertexArr[2];
     z = vertexArr[4];

     int xa = vertexArr[1];
     int  xb = vertexArr[1];
     int xc = vertexArr[1];
    cout << x << " " << xa << " " << y << " " << xb << " " << z << " " << xc << endl;
}
void Vertex::parseCoordinates(string input){
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

float * Vertex::toArray()
{
    float a[3];
    a[0] = this -> x;
    a[1] = this -> y;
    a[2] = this -> z;

    return a;
}

void Vertex::print()
{
   cout << this -> x << " , " << this -> y << " , " << this -> z << endl;

}
