#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){
    glClearColor(.753, 0, .46, 0);
    glEnable (GL_LIGHTING);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //glScalef (0.5, 0.5, 0.5);
    //glTranslatef(0,0,1.0);
    //glOrtho(-1,0.02,0,2,0,1);

    //glDisable(GL_CULL_FACE);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glRotatef(1,1,1,0);
    /* refer to boxes for examples on interaction */
    glBegin(GL_TRIANGLES);

    if (objPtr){
        Vertex v;
        face f;
        //Face actualF();
        std::vector<float> normal;

        Vertex v1, v2, v3;
        //std::cout << vertices.at(0).getX() << " " << vertices.at(0).getY() << " " << vertices.at(0).getZ() << std::endl;

            for (unsigned i = 0 ; i < faces.size() ; i++)
            {
                f = faces.at(i);
                v1 = f.getVertex(1);
                v2 = f.getVertex(2);
                v3 = f.getVertex(3);
                normal = f.getNormal();

                /* Open GL Stuff */
                glColor4f(0,1,1,1);
                glNormal3f(normal.at(0), normal.at(1), normal.at(2));
                /***************************** CHECK ORDER  ***********************************/
                glVertex3f(v1.getX(), v1.getY(), v1.getZ());
                glVertex3f(v2.getX(), v2.getY(), v2.getZ());
                glVertex3f(v3.getX(), v3.getY(), v3.getZ());

            }
    }
    glEnd();
}

void GLWidget::grabObj(objLoad objFile){
    /* TO DO , CLEAN UP UNUSED OBJFILES */
    objPtr = &objFile;
    vertices = objPtr->getVertices();
    faces = objPtr->getFacets();
}


void GLWidget::resizeGL(int w, int h){

}

void GLWidget::mousePressEvent(QMouseEvent *e)
{

}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{

}
