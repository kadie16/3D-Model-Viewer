#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    cout << endl;
    return a.exec();
}
