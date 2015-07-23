#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QQuaternion>
#include <QMouseEvent>
#include <math.h>
#include <QTime>
#include "objload.h"

class camera
{    
public:
    camera();
    void setZoom(float factor);
    void translate(float dx, float dy);
    void findModel(objLoad *o);
    void viewModel();
    void moveToCenter();
private:
    std::vector<float> center;
    float radius;
    float zoomF;
    float aspect;
    double fov;
    double left;
    double right;
    double top;
    double bottom;
    double near;
    double far;
    double fdist;
};

#endif // TRACKBALL_H
