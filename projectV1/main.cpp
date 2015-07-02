#include "mainwindow.h"
#include "objload.h"
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    string fileName;
    cout << "Please enter a filepath :  ";
    cin >> fileName;
    objLoad loader(fileName);
    loader.print();
    cout << endl;
    return 0;

    return a.exec();
}
