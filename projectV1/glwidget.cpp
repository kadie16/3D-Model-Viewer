#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){
    glClearColor(.753, 0, .46, 0);
    glShadeModel (GL_SMOOTH);



}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(1,1,1,0);
    /* load coordinates into triangles through loop */
    /* refer to boxes for examples on interaction */
    glBegin(GL_TRIANGLES);

    if (objPtr){
        Vertex v;
        Vertex f;
        Face actualF();
        float normal[3];

        Vertex v1, v2, v3;

            for (unsigned i = 0 ; i < faces.size() ; i++)
            {
                /* x, y, z in face f are the indices of the vertices that make that face */
                /* need to glVertex3f for each vertex */
                f = faces.at(i);
                v1 = vertices.at(f.getX() - 1);
                v2 = vertices.at(f.getY() - 1);
                v3 = vertices.at(f.getZ() - 1);
                /* TO DO, GIVE OPEN GL NORMALS AND ASSIGN LIGHTING */
                glColor3f(0,1,1);
                glVertex3f(v1.getX(), v1.getY(), v1.getZ());
               // glColor3f(0,0,0);
                glVertex3f(v2.getX(), v2.getY(), v2.getZ());
                glVertex3f(v3.getX(), v3.getY(), v3.getZ());
            }
    }
    glEnd();

}

void GLWidget::grabObj(objLoad objFile){
    objPtr = &objFile;
    vertices = objPtr->getVertices();
    faces = objPtr->getFacets();

    /* load coordinates into triangles through loop */
    /* refer to boxes for examples on interaction */

}


void GLWidget::resizeGL(int w, int h){

}
