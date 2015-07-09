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
    int tokenCount = 0;
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

    }
    /* TO DO : FIX THIS, ADJUST by tokenCount */
     x = vertexArr[0];
     y = vertexArr[2];
     z = vertexArr[4];


}
void Vertex::parseCoordinates(string input){
    float vertexArr[3];
    sscanf(input.c_str(), "%*s %f %f %f", &vertexArr[0], &vertexArr[1], &vertexArr[2]);
    x = vertexArr[0];
    y = vertexArr[1];
    z = vertexArr[2];
    cout << x << " " << y << " " << z << endl;
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
    /* CHECK ORDER OF VERTICES, SHOULD BE SAME AS ENTERED IN FILE */
    /* MOVE NORMAL INTO FACE CLASS */
    /* vectors */
    /***************************** CHECK ORDER  ***********************************/
    float va[3], vb[3], vr[3], val;
    va[0] = v2.getX() - x;
    va[1] = v2.getY() - y;
    va[2] = v2.getZ() - z;

    vb[0] = x - v3.getX();
    vb[1] = y - v3.getY();
    vb[2] = z - v3.getZ();

    /* cross product */
    vr[0] = va[1] * vb[2] - vb[1] * va[2];
    vr[1] = vb[0] * va[2] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - vb[0] * va[1];

    /* normalize */
    val = sqrt(vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2]);

    normal.push_back(vr[0]/val);
    normal.push_back(vr[1]/val);
    normal.push_back(vr[2]/val);

    return normal;
}
