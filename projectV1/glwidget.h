#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>
#include <QTimer>
#include "objload.h"
#include "vertex.h"
#include "face.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void grabObj(objLoad objFile);
    void resizeGL(int w, int h);
private:
    QTimer timer;
    // make function to set objFile
    objLoad *objPtr;
    std::vector<Vertex> vertices;
    std::vector<Vertex> faces;
};

#endif // GLWIDGET_H
