#include "objload.h"
using namespace std;

objLoad::objLoad(string fName)
{
    cout << "Loading object from file:  " << fName << endl;
    fileName = fName;
    /* open file stream */
    ifstream stream(fName.c_str());
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
}

string objLoad::getFileName()
{
    return fileName;
}

int main()
{
    string fileName;
    cout << "Please enter a filename:  ";
    cin >> fileName;
    objLoad loader(fileName);
    for (double v : loader.vertices)
    {
        cout << v << endl;
    }
    cout << endl;
    return 0;

}
