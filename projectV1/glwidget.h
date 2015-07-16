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
#include <QQuaternion>

#include <QMatrix4x4>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    bool toggleRotation();
    bool toggleCulling();
    bool toggleTranslation();
    double increaseScale();
    double decreaseScale();
    void setScale();
    void initializeGL();
    void paintGL();
    void drawObject();
    void resetView();
    void grabObj(objLoad objFile);
    void grabColor(double r, double g, double b);
    void resizeGL(int w, int h);
    void mouseMoveEvent(QMouseEvent *e);
    int x,y,dx,dy,x0,y0;
private:
    QTimer timer;
    objLoad *objPtr;
    std::vector<Vertex> vertices;
    std::vector<face> faces;
    std::vector<float> center;
    /* frustrum stuff */
    float radius;
    float fdist;
    double dNear;
    double dFar;
    double viewAngle;
    /* user control */
    bool mouseHeld;
    bool rotationOK;
    bool cullingOK;
    bool translateOK;
    bool scaleOK;
    double scale;
    double red,green,blue;
    bool needsReset;
signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Released();

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
};

#endif // GLWIDGET_H
