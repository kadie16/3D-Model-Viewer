#include "camera.h"

camera::camera()
{
    zoomF = 1;
}

void camera::translate(float dx, float dy)
{
    glMatrixMode(GL_PROJECTION);
    glTranslatef(dx,dy,0);
}

void camera::findModel(objLoad *o)
{
    radius = o->findRadius();
    center = o->findCenter();
    double diameter = radius*2;
    fov = 900;
    fdist = radius/tan(fov);
    near = fdist - diameter;
    far = fdist + diameter;
    left = aspect*bottom; //center.at(0) - radius;
    right = aspect*top; //center.at(0) + radius;
    top = tan(fov*0.5)*near; //center.at(1) + radius;
    bottom = -top; //center.at(1) - radius;
}

void camera::adjustAspect(float w, float h)
{
    aspect = w/h;
    if (aspect < 1)
    {
        bottom/=aspect;
        top/=aspect;
    }
    else
    {
        left*=aspect;
        right*=aspect;
    }
    this->viewModel();
}

void camera::viewModel()
{
    glMatrixMode(GL_PROJECTION);
    glOrtho(left,right,bottom,top,near,far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-center.at(0), -center.at(1), -center.at(2));
}

void camera::setZoom(float factor)
{
    zoomF = factor;
    glMatrixMode(GL_PROJECTION);
    glFrustum(left*zoomF, right*zoomF, bottom*zoomF, top*zoomF, near, far);
    glMatrixMode(GL_MODELVIEW);
}
