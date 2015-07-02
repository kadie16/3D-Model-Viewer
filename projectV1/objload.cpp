#include "objload.h"
using namespace std;

objLoad::objLoad(string fName)
{
    cout << "Loading object from path:  " << fName << endl;
    fileName = fName;
    /* open file stream */
    //ifstream stream(fName.c_str());
    ifstream stream("/Users/Kadie/Documents/kadiesworkspace/A-STAR-IHPC-Project/projectV1/test.obj");
    if (stream.is_open())
    {
        /* fill vertices */
        string currLine;
        while (!stream.eof())
        {
            /* still need to implement vertices vs. facet separation */
            getline(stream, currLine);
            int x, y, z;
            string type;
            stringstream ss(currLine);
            ss >> type;
            if (type[0] == 'v')
            {
                stringstream ss(currLine);
                ss >> x >> y >> z;
                //cout << x << ' , ' << y << ' , ' << z << endl;
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
            if (type[0] == 'f')
            {
                stringstream ss(currLine);
                ss >> x >> y >> z;
                facets.push_back(x);
                facets.push_back(y);
                facets.push_back(z);
            }
        }
        stream.close();
    } else
    {
        cout << "File load failed" << endl;
    }
}

string objLoad::getFileName()
{
    return fileName;
}

void objLoad::print()
{
    for (double v : vertices)
    {
        cout << v << endl;
    }
}

