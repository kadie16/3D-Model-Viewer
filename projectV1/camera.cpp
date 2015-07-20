#include "camera.h"

camera::camera()
{

}

void camera::translate(float dx, float dy)
{
    glMatrixMode(GL_PROJECTION);
    glTranslatef(dx,dy,0);
}

void camera::zoom(float dz)
{
    glMatrixMode(GL_PROJECTION);
    glTranslatef(0,0,dz);
}
