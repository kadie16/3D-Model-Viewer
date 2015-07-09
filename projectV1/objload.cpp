#include "objload.h"
using namespace std;

objLoad::objLoad(string fName)
{
    cout << "Loading object from path:  " << fName << endl;
    fileName = fName;
    /* open user input file stream */
    ifstream stream(fName.c_str());
    /* open hard coded file stream */
    //ifstream stream("/Users/Kadie/Downloads/BerkeleyGarmentLibrary/Garments/blouse/coarse/blouse.obj");
    if (stream.is_open())
    {
        /* fill vertices */
        string currLine;
        while (!stream.eof())
        {
            /* TO DO: consider using (string?)stream instead of getline everytime */
            getline(stream, currLine);

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
    int tokenCount = 0;
    input.erase(0,1); // delete the f
    string delimiter = "/";
    size_t pos = 0;
    string token;
    string token2;
    int index;
    int prevIndex = 0;
    vector<Vertex> toReturn;
    while ((pos = input.find(delimiter) != string::npos))
    {
     token = input.substr(0, input.find(delimiter)); // token indicates index of vertex
     istringstream(token) >> index;
     if (index != prevIndex){
        tokenCount ++; //count index tokens
        cout << tokenCount << " : " << index << endl;
        vertices.at(index -1).print();
        toReturn.push_back(vertices.at(index - 1));
        prevIndex = index;

     }

     token2 = input.substr(input.find(delimiter), input.find(' ')); //tossing token2 for now
     input.erase(0, token.length() + token2.length());
    }
    return toReturn;
}

