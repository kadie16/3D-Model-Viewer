#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
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

void MainWindow::on_toolButton_3_clicked()
{
    bool on = ui->widget16->toggleTranslation();
    if (on)
        ui->toolButton_3->setDown(true);
}

void MainWindow::on_toolButton_4_pressed()
{
    ui->widget16->increaseScale();
}

void MainWindow::on_toolButton_5_pressed()
{
    ui->widget16->decreaseScale();
}

void MainWindow::on_toolButton_4_released()
{
    ui->widget16->setScale();
}

void MainWindow::on_toolButton_5_released()
{
    ui->widget16->setScale();
}
