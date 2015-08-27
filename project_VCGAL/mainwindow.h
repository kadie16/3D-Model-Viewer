#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QSpinBox>
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

    void on_radioButton_2_stateChanged();

    void on_radioButton_2_toggled(bool checked);
    void on_toolButton_4_clicked();

    void on_checkBox_2_toggled(bool checked);

    void on_checkBox_3_toggled(bool checked);

    void on_checkBox_4_toggled(bool checked);

private:
    QTimer timer;
    Ui::MainWindow *ui;
    QSpinBox *ui_spin;
    QLabel *ui_fps;
    QLabel *ui_volStat;
    bool volStatReset;
};

#endif // MAINWINDOW_H
