#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    std::string fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Object File (*.obj)"
                ).toStdString();
    objLoad loader(fileName);
    ui -> widget16 -> paintGL(loader);
}
