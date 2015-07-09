#include "objload.h"
using namespace std;

objLoad::objLoad(string fName)
{
    cout << "Loading object from path:  " << fName << endl;
    fileName = fName;
    /* Open file stream */
    ifstream stream(fName.c_str());
    if (stream.is_open())
    {
        string currLine;
        while (!stream.eof())
        {
            /* Get next line of file */
            getline(stream, currLine);
            /* Determine whether it is a vertex, normal, or face line */
            if (currLine[0] == 'v' && currLine[1] == ' ')
            {
                Vertex v(currLine, currLine[0]);
                vertices.push_back(v);
             }
            else if (currLine[0] == 'v' && currLine[1] == 'n')
            {
                Vertex n(currLine, currLine[1]);
                normals.push_back(n);
            }

            else if (currLine[0] == 'f' && currLine[1] == ' ')
            {
                vector<Vertex> v = this->parseFace(currLine);
                face f = face(v.at(0), v.at(1), v.at(2));
                facets.push_back(f);
            }
        }
        stream.close();
    } else
    {
        cout << "File load failed!" << endl;
    }
}

string objLoad::getFileName()
{
    return fileName;
}

void objLoad::print()
{
    cout << fileName << " vertices: " << endl;
    for (unsigned i = 0 ; i < vertices.size(); i++)
    {
       vertices.at(i).print();
    }
}

vector<Vertex> objLoad::getVertices()
{
    return vertices;
}

vector<face> objLoad::getFacets()
{
    return facets;
}

vector<Vertex> objLoad::parseFace(string input){
    vector<Vertex> toReturn;
    /* Parses differently, depending on if there are slashes in line */
    if (input.find("/") != string::npos) {
        /* remove the "f" in front of the line */
        input.erase(0,1);
        string delimiter = "/";
        size_t pos = 0;
        string token;
        string token2;
        int index;
        int prevIndex = 0;
        while ((pos = input.find(delimiter) != string::npos))
        {
         /* Token is index of vertex in the face */
         token = input.substr(0, input.find(delimiter));
         istringstream(token) >> index; /* Only succeeds if token is an integer */
         if (index != prevIndex){
            /* .obj file is indexed at 1, C++ vector indexed at 0 */
            toReturn.push_back(vertices.at(index - 1));
            prevIndex = index;
        }
         /* Tossing out token2 until further notice */
         token2 = input.substr(input.find(delimiter), input.find(' '));
         /* Erases everything up until next index */
         input.erase(0, token.length() + token2.length());
        }
    } else {
        /* If there aren't any slashes, parses like coordinates */
        float vertexArr[3];
        sscanf(input.c_str(), "%*s %f %f %f", &vertexArr[0], &vertexArr[1], &vertexArr[2]);
        toReturn.push_back(vertices.at(vertexArr[0] - 1));
        toReturn.push_back(vertices.at(vertexArr[1] - 1));
        toReturn.push_back(vertices.at(vertexArr[2] - 1));
    }
    return toReturn;
}

