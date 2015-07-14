#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>
#include <QTimer>
#include <QVector2D>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include "objload.h"
#include "vertex.h"
#include "face.h"

#include <QMatrix4x4>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    bool toggleRotation();
    bool toggleCulling();
    bool toggleTranslation();
    void initializeGL();
    void paintGL();
    void grabObj(objLoad objFile);
    void resizeGL(int w, int h);
    void mouseMoveEvent(QMouseEvent *e);
    int x,y,dx,dy,x0,y0;
private:
    QTimer timer;
    objLoad *objPtr;
    std::vector<Vertex> vertices;
    std::vector<face> faces;
    bool mouseHeld;
    bool rotationOK;
    bool cullingOK;
    bool translateOK;
signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();
    void Mouse_Released();

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void leaveEvent();
};

#endif // GLWIDGET_H
