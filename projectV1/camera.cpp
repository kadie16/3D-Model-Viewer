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
    glMatrixMode(GL_PROJECTION);
    glTranslatef(dx,dy,0);
}

void camera::findModel(objLoad *o)
{
    radius = o->findRadius();
    center = o->findCenter();
    double diameter = radius*2;
    fov = 90;
    //fov*= M_PI/180;
    fdist = radius/tan(fov*0.5);
    near = fdist - diameter;
    far = fdist + diameter;
    /*
    left =  center.at(0) - radius;
    right =  center.at(0) + radius;
    top =   center.at(1) + radius;
    bottom = center.at(1) - radius; */

    top =   tan(fov*0.5)*near;
    bottom = -top;
    right =  aspect*top;
    left =  aspect*bottom;
}

void camera::viewModel()
{
    //left = left*.5; right = right*.5; bottom = bottom*.5; top = top*.5;
    glMatrixMode(GL_PROJECTION);
    //glOrtho(left*zoomF,right*zoomF,bottom*zoomF,top*zoomF,near,far);
    glFrustum(left,right,bottom,top,near,far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void camera::moveToCenter()
{
    glTranslatef(-center.at(0), -center.at(1), -center.at(2));
}

void camera::setZoom(float factor)
{
    zoomF = factor;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left*zoomF,right*zoomF,bottom*zoomF,top*zoomF,near,far);
}


