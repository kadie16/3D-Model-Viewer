#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>
#include <QTimer>
#include <QVector2D>
#include <QMouseEvent>
#include "objload.h"
#include "vertex.h"
#include "face.h"
#include <QMatrix4x4>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void grabObj(objLoad objFile);
    void grabWidth(int w);
    void grabHeight(int h);
    void resizeGL(int w, int h);
    void perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
private:
    int winW;
    int winH;
    QTimer timer;
    objLoad *objPtr;
    std::vector<Vertex> vertices;
    std::vector<face> faces;

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
};

#endif // GLWIDGET_H
