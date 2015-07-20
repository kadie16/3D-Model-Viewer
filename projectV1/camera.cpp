#include "camera.h"

camera::camera(float angV, QVector3D ax)
{
    angularV = angV;
    axis = ax;
    rotation = QQuaternion();
}

void camera::move()
{
    float msecs = lastTime.msecsTo(QTime::currentTime());
    QVector3D lastPos = position(x0,y0);
    QVector3D currPos = position(x , y);
    axis = QVector3D::crossProduct(lastPos,currPos);
    float angle = 180/M_PI*asin(sqrt(QVector3D::dotProduct(this->axis, this->axis)));
    angularV = angle/msecs;
    axis.normalize();
    rotation = QQuaternion::fromAxisAndAngle(axis, angle) * rotation;
}

QQuaternion camera::rotate()
{
    if (!mouseHeld)
        return rotation;
    float ang = angularV * lastTime.msecsTo(QTime::currentTime());
    return (QQuaternion::fromAxisAndAngle(axis, ang) * rotation);
}

QVector3D camera::position(float xIn, float yIn)
{
    QVector3D pos = QVector3D(xIn,yIn,0);
    float sqrZ = 1 - QVector3D::dotProduct(pos, pos);
    if (sqrZ > 0)
        pos.setZ(sqrt(sqrZ));
    else
        pos.normalize();
    return pos;
}


void camera::mousePressEvent(QMouseEvent *e)
{
    mouseHeld = true;
    x0 = e->x();
    y0 = e->y();
    lastTime = QTime::currentTime();
}

void camera::mouseReleaseEvent(QMouseEvent *e)
{
    mouseHeld = false;
    x0 = 0;
    y0 = 0;
}

void camera::mouseMoveEvent(QMouseEvent *e){
    this->x = e->x();
    this->y = e->y();
}
