#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>
#include <QT>
#include <QTimer>
#include <QVector2D>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <QQuaternion>
#include <QObject>
#include <QLabel>
#include <QMatrix4x4>
#include "camera.h"

typedef Polyhedron::HalfedgeDS HDS;
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    bool toggleRotation();
    bool toggleCulling();
    bool toggleVolume();
    bool toggleTranslation();
    void initializeGL();
    void paintGL();
    void drawVolume();
    void drawModel(model mod);
    void drawQuad(Polyhedron::Facet_const_handle f);
    void drawAxes();
    void resetView();
    void grabObj(objLoad<HDS> objFile);
    void grabColor(double r, double g, double b);
    void resizeGL(int w, int h);
    void mouseMoveEvent(QMouseEvent *e);
    QQuaternion drag2Rotate(float dx, float dy, model mod);
    void processModelControls(model mod, float dx, float dy);
    void drag2Translate(float dx, float dy);
    void drag2Zoom(float dy);
    int giveFPS();
    bool generateVolumeMesh();
    bool toggleDrawPlane();
    void drawPlane(float startX, float startY);

private:
    QTime frameTimer;
    int frameCount;
    QTimer timer;
    /* .obj Information */
    objLoad<HDS> *objPtr = 0;
    std::vector<float> center;
    std::vector<float> maxCoords;
    std::vector<float> minCoords;
    QQuaternion currQ;
    /* Frustrum Things */
    float radius;
    float w0;
    float h0;
    /* User Control */
    camera cam;
    /* Rotation */
    bool mouseHeld;
    bool rotationOK;
    /* Culling */
    bool cullingOK;
    bool translateOK;
    bool scaleOK;
    /* Zoom */
    bool zoomOK;
    float zoomF;
    double scale;
    /* Color Pick */
    double red,green,blue;
    bool needsReset;
    QVector3D axisOfRotation;
    float transX, transY;
    int x,y,dx,dy,x0,y0;
    int prevPos[2];
    float mag;
    /* Drawing */
    CGAL::Vector_3<Kernel> n1, n2, n3;
    CGAL::Point_3<Kernel> p1,p2,p3,p4;
    Polyhedron::Halfedge_const_handle h;
    /* Volume Mesh */
    Polyhedron mesh;
    Mesh_Polyhedron mesh_Poly;
    bool volumeOK;
    bool drawingPlane;
    C3T3 c3t3;
    Tr t;
    model m;
signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Released();
protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
};

#endif // GLWIDGET_H
