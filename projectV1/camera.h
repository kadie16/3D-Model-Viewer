#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QQuaternion>
#include <QMouseEvent>
#include <math.h>
#include <QTime>

class camera
{
public:
    camera(float angVel, QVector3D ax);
    void move();
    QQuaternion rotate();
private:
    float angularV;
    QVector3D axis;
    float x0,y0,x,y;
    QTime lastTime;
    QQuaternion rotation;
    bool mouseHeld;
    static QVector3D position(float xIn , float yIn);
protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // TRACKBALL_H
