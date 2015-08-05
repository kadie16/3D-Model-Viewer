#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>
#include <QT>
#include <QTimer>
#include <QVector2D>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include "camera.h"
#include <QQuaternion>
#include <QObject>
#include <QLabel>
#include <QMatrix4x4>

typedef Polyhedron::HalfedgeDS HDS;
typedef map<Polyhedron::Facet_const_handle, CGAL::Vector_3<Kernel> > facetVectorMap;
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
    void drawObject();
    void drawVolume();
    void drawTriangle(Polyhedron::Facet_const_handle f);
    void drawQuad(Polyhedron::Facet_const_handle f);
    void computeNormals();
    void drawAxes();
    void resetView();
    void grabObj(objLoad<HDS> objFile);
    void grabColor(double r, double g, double b);
    void resizeGL(int w, int h);
    void mouseMoveEvent(QMouseEvent *e);
    QQuaternion drag2Rotate(float dx, float dy);
    void drag2Translate(float dx, float dy);
    void drag2Zoom(float dy);
    int giveFPS();
    C3T3 generateVolumeMesh();

private:
    QTime frameTimer;
    int frameCount;
    QTimer timer;
    /* .obj Information */
    objLoad<HDS> *objPtr = 0;
    Polyhedron mesh;
    facetVectorMap normals;
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
    int x,y,dx,dy,x0,y0;
    int prevPos[2];
    float mag;
    /* Drawing */
    CGAL::Vector_3<Kernel> n1, n2, n3;
    CGAL::Point_3<Kernel> p1,p2,p3;
    Polyhedron::Halfedge_const_handle h;
    /* Volume Mesh */
    C3T3 c3t3;
    Tr t;
signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Released();
protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
};

#endif // GLWIDGET_H
