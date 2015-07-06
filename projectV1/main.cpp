#include "mainwindow.h"
#include "objload.h"
#include <QApplication>
#include <QFileDialog>

using namespace std;

int main(int argc, char *argv[])
{

   // QString fileName;
    //cout << "Please enter a filepath :  ";
    //cin >> fileName;
    //objLoad loader(fileName);
   // loader.print();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    cout << endl;
    return a.exec();
}
