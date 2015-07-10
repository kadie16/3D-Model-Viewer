#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
    winW = this->width();
    winH = this->height();
}

void GLWidget::initializeGL(){
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

    glClearColor(.753, 0, .46, 0);
    /* Light Settings */
    GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glShadeModel( GL_SMOOTH );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_BLEND);
    glScalef (1, 1, 1);
    //perspective(10, 1, 0, 10);
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

void GLWidget::perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * M_PI / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
    std::cout << "meow";
}
