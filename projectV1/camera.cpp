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

    fov = 30;
    //fov*= M_PI/180;
    fdist = radius/tan(fov*0.5);
    near = fdist - diameter;
    far = fdist + diameter;
    top =   tan(fov*0.5)*near;
    bottom = -top;
    right =  aspect*top;
    left =  aspect*bottom;

    /*
    left =  center.at(0) - radius;
    right =  center.at(0) + radius;
    top =   center.at(1) + radius;
    bottom = center.at(1) - radius;
    near = center.at(2) - radius;
    far = center.at(2) + radius; */
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
    glTranslatef(-center.at(0), -center.at(1), -(center.at(2)));
}

float camera::fitModel(float xMax, float xMin, float yMax, float yMin, float zMax, float zMin)
{
    float dx = xMax - xMin;
    float dy = yMax - yMin;
    float dz = zMax - zMin;

    if (dx > dy && dx > dz)
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

void camera::setZoom(float factor)
{
    if (factor > 0.01)
        zoomF = factor;
    else
        zoomF = 0.01;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left*zoomF,right*zoomF,bottom*zoomF,top*zoomF,-near,-far);
}
