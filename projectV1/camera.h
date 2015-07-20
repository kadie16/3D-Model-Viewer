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
    void zoom(float dz);
    void translate(float dx, float dy);
};

#endif // TRACKBALL_H
