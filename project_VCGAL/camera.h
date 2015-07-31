#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QQuaternion>
#include <QMouseEvent>
#include <math.h>
#include <QTime>
#include "objload.h"
#include <CGAL/HalfedgeDS_default.h>
#include <CGAL/HalfedgeDS_min_items.h>

class camera
{    
public:
    typedef CGAL::HalfedgeDS_default HDS<int, CGAL::HalfedgeDS_min_items>;
    camera();
    void setAspect(float w, float h);
    void setZoom(float factor);
    void translate(float dx, float dy);
    void findModel(objLoad<HDS> *o);
    void viewModel();
    void moveToCenter();
    void adjustZoom();
    void adjustAspect(float w, float h);
    float fitModel(float xMax, float xMin, float yMax, float yMin, float zMax, float zMin);
private:
    std::vector<float> center;
    float radius;
    float zoomF;
    float aspect;
    float w0;
    double fov;
    double left;
    double leftAdjust;
    double right;
    double rightAdjust;
    double top;
    double bottom;
    double near;
    double far;
    double fdist;
};

#endif // TRACKBALL_H
