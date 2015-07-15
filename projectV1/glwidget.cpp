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
    //glEnable( GL_COLOR_MATERIAL );
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glScalef (1, 1, 1);
   //glFrontFace(GL_CW);
    mouseHeld = false;
    rotationOK = false;
    translateOK = false;
    cullingOK = false;
    /* "If you want to move the camera up, you have to move the world down instead*/
    /* - https://open.gl/transformations */
    glTranslatef(0,-1,0); /* Moves "camera" up one unit */
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    if (mouseHeld && rotationOK && !translateOK)
    {
        int yRot, xRot, mag;
        xRot = - dx / 10;
        yRot = - dy / 10;
        mag = sqrt(xRot*xRot + yRot* yRot)/10;
        glRotatef(mag,0,xRot,yRot);
    }
    if (cullingOK)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else
        glDisable(GL_CULL_FACE);
    if (mouseHeld && translateOK && !rotationOK)
    {
        int xT, yT;
        xT = - dx / 1000;
        yT = - dy / 1000;
        glTranslatef(dx,dy,0);
    }

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
                /* Rendering Face (OpenGL Stuff) */
                glColor3f(.86,.63,.75);
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
    mouseHeld = true;
    x0 = x;
    y0 = y;
    emit Mouse_Pressed();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mouseHeld = false;
    x0 = 0;
    y0 = 0;
    emit Mouse_Released();
}

void GLWidget::mouseMoveEvent(QMouseEvent *e){
    this->x = e->x();
    this->y = e->y();
    emit Mouse_Pos();
    if (mouseHeld)
    {
        dx = x - x0;
        dy = y - y0;
        std::cout<< dx << " , " << dy << std::endl;
    }
}

bool GLWidget::toggleRotation(){
    if (rotationOK)
        rotationOK = false;
    else
        rotationOK = true;
    return rotationOK;
}

bool GLWidget::toggleCulling()
{
    if (cullingOK)
        cullingOK = false;
    else
        cullingOK = true;
    return cullingOK;
}

bool GLWidget::toggleTranslation()
{
    if (translateOK)
        translateOK = false;
    else
        translateOK = true;
    return translateOK;
}
