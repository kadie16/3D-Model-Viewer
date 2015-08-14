#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    ui_fps = findChild<QLabel*>("fps");
    ui_volStat = findChild<QLabel*>("volStatus");
    volStatReset = false;
    ui_volStat->setText(" ");
    ui->radioButton->setChecked(true);
    ui->radioButton_4->setChecked(true);
    ui->radioButton_2->setEnabled(false);
    connect(&timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::repaint() {
    ui_fps->setNum(ui->widget16->giveFPS());
}

void MainWindow::on_toolButton_2_clicked()
{
    std::string fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/Users/Kadie/Documents/kadiesworkspace/A-STAR-IHPC-Project/projectV1/testFiles/",
                "Object File (*.obj)"
                ).toStdString();
    objLoad<HDS> loader(fileName);
    //loader.print();
    ui->widget16->grabObj(loader);
}
void MainWindow::on_quitButton_clicked()
{
    close();
}

void MainWindow::on_checkBox_stateChanged()
{
    ui->widget16->toggleCulling();
}

void MainWindow::on_toolButton_3_clicked()
{
    bool on = ui->widget16->toggleTranslation();
    if (on)
        ui->toolButton_3->setDown(true);
}

void MainWindow::on_toolButton_6_clicked()
{
    QColor color = QColorDialog::getColor();
    ui->widget16->grabColor(color.red(), color.green(), color.blue());
}


void MainWindow::on_toolButton_clicked()
{
    ui_volStat->setText("Loading...");
<<<<<<< HEAD
    ui->widget16->generateVolumeMesh();
    ui_volStat->setText("Done!");
=======
    bool success = ui->widget16->generateVolumeMesh();
    if (success) {
        ui_volStat->setText("Done!");
        ui->radioButton_2->setEnabled(true);
    }
    else {
        ui_volStat->setText("Failed!!!!");
        ui->radioButton_2->setEnabled(false);
    }
>>>>>>> f8a6ad4... independent rotation, translation slightly off
}

void MainWindow::on_radioButton_2_stateChanged()
{

}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    ui->widget16->toggleVolume();
}
