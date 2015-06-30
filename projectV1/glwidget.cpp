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
    glBegin(GL_TRIANGLES);
        glColor3f(0,1,1);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(1,0,1);
        glVertex3f( 0.5, -0.5, 0);
        glColor3f(0,0,1);
        glVertex3f( 0.0,  0.5, -0.5);
    glEnd();
}

void GLWidget::resizeGL(int w, int h){

}
