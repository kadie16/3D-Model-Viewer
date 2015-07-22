#include "camera.h"

camera::camera()
{

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
    viewAngle = 90;
    fdist = radius/tan(viewAngle);
    near = fdist - diameter;
    far = fdist + diameter;
    left = center.at(0) - radius;
    right = center.at(0) + radius;
    bottom = center.at(1) - radius;
    top = center.at(1) + radius;
}

void camera::viewModel()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(left,right,bottom,top,near,far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-center.at(0), -center.at(1), -center.at(2));
}

void camera::zoom(float dz)
{
    glMatrixMode(GL_PROJECTION);
    glTranslatef(0,0,dz);
}
