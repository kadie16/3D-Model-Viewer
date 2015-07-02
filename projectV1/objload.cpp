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
            /* still need to implement vertices vs. facet separation */
            getline(stream, currLine);
            //cout << currLine << endl;

            if (currLine[0] == 'v')
            {
                Vertex v(currLine);
                vertices.push_back(v);
             }

            if (currLine[0] == 'f')
            {
                Vertex f(currLine);
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

