#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){
    glClearColor(.753, 0, .46, 0);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    glRotatef(0.5,1,1,1);
    /* load coordinates into triangles through loop */
    /* refer to boxes for examples on interaction */
    glBegin(GL_TRIANGLES);

    //MANUAL TRIANGLE
        glColor3f(0,1,1);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(1,0,1);
        glVertex3f( 0.5, -0.5, 0);
        glColor3f(0,0,1);
        glVertex3f( 0.0,  0.5, -0.5);
    glEnd();
}

void GLWidget::paintGL(objLoad objFile){
    std::vector<Vertex> vertices = objFile.getVertices();
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(0.5,1,1,1);
    Vertex v;
    /* load coordinates into triangles through loop */
    /* refer to boxes for examples on interaction */
    glBegin(GL_TRIANGLES);
    for (unsigned i = 0 ; i < vertices.size() ; i++)
    {
        v = vertices.at(i);
        glVertex3f(v.getX(), v.getY(), v.getZ());
     }
    glEnd();
}


void GLWidget::resizeGL(int w, int h){

}
