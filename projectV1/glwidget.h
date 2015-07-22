#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>
#include <QT>
#include <QTimer>
#include <QVector2D>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include "objload.h"
#include "vertex.h"
#include "face.h"
#include "camera.h"
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
    void drawAxes();
    void resetAxes();
    void resetView();
    void grabObj(objLoad objFile);
    void grabColor(double r, double g, double b);
    void resizeGL(int w, int h);
    void mouseMoveEvent(QMouseEvent *e);
    void rotateCenter(QQuaternion q);

private:
    QTimer timer;
    /* .obj Information */
    objLoad *objPtr;
    std::vector<Vertex> vertices;
    std::vector<face> faces;
    std::vector<float> center;
    std::vector<float> maxCoords;
    std::vector<float> minCoords;
    QQuaternion currQ;
    /* Frustrum Things */
    float radius;
    float fdist;
    double dNear;
    double dFar;
    double viewAngle;
    /* User Control */
    camera cam;
    /* Rotation */
    bool mouseHeld;
    bool rotationOK;
    bool cullingOK;
    bool translateOK;
    bool scaleOK;
    double scale;
    double red,green,blue;
    bool needsReset;
    QVector3D xAxis;
    QVector3D axisOfRotation;
    QVector3D yAxis;
    int x,y,dx,dy,x0,y0;
    int prevPos[2];
    float mag;
signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Released();
protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
};

#endif // GLWIDGET_H
