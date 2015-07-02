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
        if (currLine[0] == 'v')
        {
            Vertex v(currLine);
            vertices.push_back(v);
        }
        if (currLine[0] == 'f')
        {
            Vertex f(currLine);
            vertices.push_back(f);
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
    for (Vertex v : loader.vertices)
    {
        v.print();
    }
    cout << endl;
    return 0;

}
