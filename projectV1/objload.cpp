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
                /* TO DO: read in first number, use slash as delimeter */
                Vertex f(currLine, currLine[0]);
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
    cout << endl << fileName << " facets: " << endl;
    for (unsigned i = 0 ; i < facets.size(); i++)
    {
       facets.at(i).print();
    }
}

vector<Vertex> objLoad::getVertices()
{
    return vertices;
}

vector<Vertex> objLoad::getFacets()
{
    return facets;
}
