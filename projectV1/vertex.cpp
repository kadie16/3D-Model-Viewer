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

float Vertex::getX()
{
    return x;
}

float Vertex::getY()
{
    return y;
}

float Vertex::getZ()
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

void Vertex::assignNormal(float v1, float v2, float v3){
    normal.push_back(v1);
    normal.push_back(v2);
    normal.push_back(v3);
}

vector<float> Vertex::getNormal(){
    return normal;
}

void Vertex::inheritNormal(Vertex parent){
    normal = parent.getNormal();
}

vector<float> Vertex::findNormal(Vertex v2, Vertex v3){



    /* vectors */
    float va[3], vb[3], vr[3], val;
    va[0] = x -v2.getX();
    va[1] = y - v2.getY();
    va[2] = z - v2.getZ();

    vb[1] = x - v3.getX();
    vb[1] = y - v3.getY();
    vb[2] = z - v3.getZ();

    /* cross product */
    vr[0] = va[1] * vb[2] - vb[1] * va[2];
    vr[1] = vb[0] * va[2] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - vb[0] * va[1];

    /* normalize */
    val = sqrt( vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2]);
    normal.push_back(vr[0]/val);
    normal.push_back(vr[1]/val);
    normal.push_back(vr[2]/val);

    return normal;
}
