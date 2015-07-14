#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QColor backColor = QColor(14,23,27);
    QColor buttonColor = QColor(54,63,67);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_2_clicked()
{
    std::string fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/Users/Kadie/Documents/kadiesworkspace/A-STAR-IHPC-Project/projectV1/testFiles/",
                "Object File (*.obj)"
                ).toStdString();
    objLoad loader(fileName);
    //loader.print();
    ui->widget16->grabObj(loader);
}

void MainWindow::on_toolButton_clicked()
{
    bool on = ui->widget16->toggleRotation();
    if (on)
        ui->toolButton->setDown(true);
}

void MainWindow::on_quitButton_clicked()
{
    close();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->widget16->toggleCulling();
}
