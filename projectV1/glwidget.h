#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>
#include <QTimer>
#include "objload.h"
#include "vertex.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL(objLoad objFile);
    void paintGL();
    void resizeGL(int w, int h);
private:
    QTimer timer;


};

#endif // GLWIDGET_H
