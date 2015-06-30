#include "objload.h"


objLoad::objLoad(string fName)
{
    cout << "Loading object from file:  " << fName << endl;
    fileName = fName;
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

}
