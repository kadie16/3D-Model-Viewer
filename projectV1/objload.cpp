#include "objload.h"
using namespace std;

objLoad::objLoad(string fName)
{
    cout << "Loading object from path:  " << fName << endl;
    fileName = fName;
    /* open user input file stream */
    //ifstream stream(fName.c_str());
    /* open hard coded file stream */
    ifstream stream("/Users/Kadie/Documents/kadiesworkspace/A-STAR-IHPC-Project/projectV1/test.obj");
    if (stream.is_open())
    {
        /* fill vertices */
        string currLine;
        while (!stream.eof())
        {
            /* still need to implement vertices vs. facet separation */
            getline(stream, currLine);
            //cout << currLine << endl;
            double x, y, z;


            if (currLine[0] == 'v')
            {
                float vertexArr[3];
                sscanf(currLine.c_str(), "%*s %f %f %f", &vertexArr[0], &vertexArr[1], &vertexArr[2]);
                vertices.push_back(vertexArr[0]);
                vertices.push_back(vertexArr[1]);
                vertices.push_back(vertexArr[2]);
             }

            if (currLine[0] == 'f')
            {
                float Facet[3];
                sscanf(currLine.c_str(), "%*s %f %f %f", &Facet[0], &Facet[1], &Facet[2]);
                facets.push_back(Facet[0]);
                facets.push_back(Facet[1]);
                facets.push_back(Facet[2]);
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
        if ((i+1) % 3 == 0)
        {
            cout << vertices.at(i) << endl;
        }
        else
        {
            cout<< vertices.at(i) << " , " ;
        }
    }
}

