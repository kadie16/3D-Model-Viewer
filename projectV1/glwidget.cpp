#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){
    glMatrixMode(GL_MODELVIEW);
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

    /* Background Setting */
    glClearColor( 1, 1, 1, 1);
    /* Light Settings */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glShadeModel( GL_SMOOTH );

    glScalef (1, 1, 1);
    /* "If you want to move the camera up, you have to move the world down instead*/
    /* - https://open.gl/transformations */
    glTranslatef(0,-1,0); /* Moves "camera" up one unit */
    //glFrontFace(GL_CW);
    //glEnable(GL_CULL_FACE);
    //
    //glCullFace(GL_BACK);

}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glRotatef(1,0,1,0);
    glBegin(GL_TRIANGLES);

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

                /* finding angles between camera to point & normal */
                float dot = normal.at(0)*v1.getX() + normal.at(1)*v1.getY() + normal.at(2)*v1.getZ();
                float l1 = normal.at(0)*normal.at(0) + normal.at(1)*normal.at(1) + normal.at(2)*normal.at(2);
                float l2 = v1.getX()*v1.getX() + v2.getY()*v2.getY() + v3.getZ()*v3.getZ();
                float angle = acos(dot/sqrt(l1*l2));

                /* Rendering Face (OpenGL Stuff) */
                if (angle < 90 && angle > - 90) /* if normal points toward camera */
                    glColor4f(1,1,0,1);
                else
                    glColor3f(1,0,0);
                glNormal3f(normal.at(0), normal.at(1), normal.at(2));
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



