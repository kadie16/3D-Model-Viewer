#include "objload.h"


objLoad::objLoad(string fName)
{
    cout << "Loading object from file:  " << fName << endl;
    fileName = fName;
    /* open file stream */
    ifstream stream(fName);
    /* determine length of file */
    is.seekg(0, ios_base::end);
    size_t size = is.tellg();
    is.seekg(0, ios_base::begin);
    /* fill vector */
    string currLine;
    while (stream.peek() !=EOF) {
        getline(stream, currLine);
    }



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
