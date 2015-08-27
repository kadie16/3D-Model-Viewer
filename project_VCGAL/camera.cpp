#include "camera.h"

camera::camera()
{
    zoomF = 1;
}

void camera::setAspect(float w, float h)
{
    aspect = w/h;
}

void camera::translate(float dx, float dy)
{
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(dx,dy,0);
}

void camera::findModel(model *m)
{
    radius = m->radius();
    modelCenter = m->center();
    double diameter = radius*2;
    fov = 30;
    fdist = radius/tan(fov*0.5);
    near = fdist - diameter;
    far = fdist + diameter;
    top =   tan(fov*0.5)*near;
    bottom = -top;
    right =  aspect*top;
    left =  aspect*bottom;
}

void camera::viewModel()
{
    glMatrixMode(GL_PROJECTION);\
    glFrustum(left,right,bottom,top,near,far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void camera::moveToCenter()
{
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-modelCenter.at(0), -modelCenter.at(1), -modelCenter.at(2));
}

void camera::adjustAspect(float w, float h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float newAspect = w/h;
    leftAdjust = newAspect * left;
    rightAdjust = newAspect * right;
    glOrtho(zoomF*leftAdjust, zoomF*rightAdjust, zoomF*bottom, zoomF*top, near, far);
}

float camera::fitModel(float xMax, float xMin, float yMax, float yMin, float zMax, float zMin)
{
    float dx = xMax - xMin;
    float dy = yMax - yMin;
    float dz = zMax - zMin;
    float diam = radius*2;
    if (dx == dy == dz)
    {
        zoomF = .9*(right-left)/diam;
        zoomF = 1/zoomF;
    }
    else if (dx >= dy && dx >= dz)
    {
        zoomF = .9*(right-left)/dx;
        zoomF = 1/zoomF;
    }
    else
    {
        float dim;
        if (dy > dz)
            dim = dy;
        else
            dim = dz;
        zoomF = .9*(top-bottom)/dim;
        zoomF = 1/zoomF;
    }
    return zoomF;
}

double camera::getNear()
{
    return near;
}

void camera::setZoom(float factor)
{
    if (factor > 0.01)
        zoomF = factor;
    else
        zoomF = 0.01;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // make sure zoom not applied to previous state
    glOrtho(leftAdjust*zoomF,rightAdjust*zoomF,bottom*zoomF,top*zoomF,-near,-far);
}


