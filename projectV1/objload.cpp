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
        getline(stream, currLine);
        Vertex v(currLine);
        vertices.push_back(v);
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
