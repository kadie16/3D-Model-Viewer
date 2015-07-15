#include "vertex.h"

using namespace std;

Vertex::Vertex()
{
    isInitialized = false;
}

Vertex::Vertex(float inX, float inY, float inZ)
{
    x = inX;
    y = inY;
    z = inZ;
}

Vertex::Vertex(string input, char type)
{
    isInitialized = false;
    if (type == 'v' || type == 'n')
    {
        this->parseCoordinates(input);
        isInitialized = true;
    }
}

bool Vertex::exists(){
    return isInitialized;
}

void Vertex::parseCoordinates(string input){
    float vertexArr[3];
    sscanf(input.c_str(), "%*s %f %f %f", &vertexArr[0], &vertexArr[1], &vertexArr[2]);
    x = vertexArr[0];
    y = vertexArr[1];
    z = vertexArr[2];
    //cout << x << " " << y << " " << z << endl;
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
bool Vertex::hasNormal(){
    return !normal.empty();
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
    float va[3], vb[3], vr[3], val;

    /* Calculate 1st Vector */
    va[0] = x - v2.getX();
    va[1] = y - v2.getY();
    va[2] = z - v2.getZ();
    /* Calculate 2nd Vector */
    vb[0] = v3.getX() - v2.getX();
    vb[1] = v3.getY() - v2.getY();
    vb[2] = v3.getZ() - v2.getZ();

    /* Cross Product */
    vr[0] = va[1] * vb[2] - vb[1] * va[2];
    vr[1] = vb[0] * va[2] - va[0] * vb[2];
    vr[2] = va[0] * vb[1] - vb[0] * va[1];
    /* Normalization Factor */
    val = sqrt(vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2]);
    normal.push_back(vr[0]/val);
    normal.push_back(vr[1]/val);
    normal.push_back(vr[2]/val);
    return normal;
}

float Vertex::checkAngle(float va[], float vb[]){
    /* Angle Check */
    float dot, alsqr, blsqr, theta;
    dot = va[0]*vb[0] + va[1]*vb[1] + va[2]*vb[2];
    alsqr = va[0]*va[0] + va[1]*va[1] + va[2]*va[2];
    blsqr = vb[0]*vb[0] + vb[1]*vb[1] + vb[2]*vb[2];
    theta = acos(dot/sqrt(alsqr*blsqr));
    return theta;
}

bool Vertex::equalsVertex(Vertex v){
    if (this->x == v.getX() && this->y == v.getY() && this->z == v.getZ()){
        vector<float> otherNormal = v.getNormal();
        if (normal.empty() && !v.hasNormal())
            return true;
        else if (normal.empty() ^ !v.hasNormal())
            return false;
        else if (std::equal(otherNormal.begin(), otherNormal.end(), this->normal.begin()))
            return true;
        else
            cout << "the normals are not equal" << endl;
    }
    else
        return false;
}
