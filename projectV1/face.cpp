#include "face.h"
using namespace std;

face::face()
{

}

face::face(Vertex first, Vertex second, Vertex third)
{
    v1 = first;
    v2 = second;
    v3 = third;
    this->findNormal();
}

face::face(string line){

}

void face::findNormal(){
    normal = v1.findNormal(v2, v3);
}

vector<float> face::getNormal(){
    return normal;
}

Vertex face::getVertex(unsigned number){
    if (number == 1){
        return v1;
    } else if (number == 2){
        return v2;
    } else if (number == 3){
        return v3;
    }
}

bool face::equalsFace(face f)
{
    if (this->v1.equalsVertex(f.getVertex(1)) && this->v2.equalsVertex(f.getVertex(2))
            && this->v3.equalsVertex(f.getVertex(3)) && this->normal == f.getNormal())
        return true;
    else
        return false;
}
