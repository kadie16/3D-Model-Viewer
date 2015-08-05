#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QMessageBox>
#include "objload.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_toolButton_2_clicked();
    void on_quitButton_clicked();

    void on_checkBox_stateChanged();

    void on_toolButton_3_clicked();

    void on_toolButton_6_clicked();
    void repaint();

    void on_toolButton_clicked();

private:
    QTimer timer;
    Ui::MainWindow *ui; 
    QLabel *ui_fps;
};

#endif // MAINWINDOW_H
