#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){
<<<<<<< HEAD
    /*glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, winW, winH); // redundant , will be useful when moving camera around
    GLfloat aspect = (GLfloat) winW / winH;
    std::cout << winW << "x" << winH;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    this->perspective(45, aspect, 1, 500);*/
    glMatrixMode(GL_MODELVIEW);
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0f, 0.1f, 0.0f, 0.5f );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

=======
>>>>>>> parent of c24dff2... latest working code, viewport stuff doesn't work
    glClearColor(.753, 0, .46, 0);
    glEnable (GL_LIGHTING);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glScalef (.01, .01, .01);
    /* "If you want to move the camera up, you have to move the world down instead*/
    /* - https://open.gl/transformations */
   // glTranslatef(0,-1,0); /* Moves "camera" up one unit */

    //glOrtho(-1,0.02,0,2,0,1);
    //glDisable(GL_CULL_FACE);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    //glRotatef(1,0,1,0);

    /* refer to boxes for examples on interaction */
   // glBegin(GL_TRIANGLES);
      glBegin(GL_LINE);
      glVertex3f(0,0,0);
      glVertex3f(1,1,-1);
    if (objPtr){
        face f;
        std::vector<float> normal;
        Vertex v1, v2, v3;
        for (unsigned i = 0 ; i < faces.size() ; i++)
            {
                /* Getting Normal and Vertices from Face */
                f = faces.at(i);
                v1 = f.getVertex(1);
                v2 = f.getVertex(2);
                v3 = f.getVertex(3);
                normal = f.getNormal();


                /* Rendering Face (OpenGL Stuff) */
               /* glColor4f(0,1,1,1);
                glNormal3f(normal.at(0), normal.at(1), normal.at(2));
                glVertex3f(v1.getX(), v1.getY(), v1.getZ());
                glVertex3f(v2.getX(), v2.getY(), v2.getZ());
                glVertex3f(v3.getX(), v3.getY(), v3.getZ());
                glEnd();*/
                //glBegin(GL_LINE);
                //glColor3f(1,1,1);
                //glVertex3f(v1.getX(), v1.getY(), v1.getZ());
                //glVertex3f(v1.getX() + normal.at(0), v1.getY() + normal.at(1), v1.getZ() + normal.at(2));

                //glBegin(GL_TRIANGLES);
                if (i == 0)
                {
                    std::cout << "vertex: " << v1.getX() << " " << v1.getY() << " " << v1.getZ() << std::endl;
                    std::cout << "normal: " << normal.at(0) << " " << normal.at(1) << " " << normal.at(2) << std::endl;
                }
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
