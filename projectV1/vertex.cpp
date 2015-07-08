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
          this ->parseCoordinates(input);
        }
    }

}

void Vertex::parseFace(string input){
    int vertexArr[3];
    QString qstr = QString::fromStdString(input);
    QRegularExpression  rx("(?<=\ )[0-9]+(?=\/)");
    int i = 0;
    while (i <= rx.match(qstr).lastCapturedIndex()){
        vertexArr[i] = atoi(rx.match(qstr).captured(i).toStdString().c_str());
    }

    x = vertexArr[0];
    y = vertexArr[1];
    z = vertexArr[2];
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

void Vertex::print()
{
   cout << this -> x << " , " << this -> y << " , " << this -> z << endl;

}

