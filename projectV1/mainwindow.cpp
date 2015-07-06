#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "objload.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Object File (*.obj)"
                );
     objLoad loader(fileName);
     std::vector<Vertex> vertices = loader.getVertices();
     glClear(GL_COLOR_BUFFER_BIT);
     glRotatef(0.5,1,1,1);
     Vertex v;
     /* load coordinates into triangles through loop */
     /* refer to boxes for examples on interaction */
     glBegin(GL_TRIANGLES);

     for (unsigned i = 0 ; i < vertices.size() ; i++)
     {
         v = vertices.at(i);
         glVertex3f(v.getX(), v.getY(), v.getZ());
      }
     glEnd();
}
