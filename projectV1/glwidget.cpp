#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_DEPTH_TEST );
    glMatrixMode(GL_MODELVIEW);
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );
    glDepthFunc( GL_LEQUAL );
    /* Background Setting */
    glClearColor( 1, 1, 1, 1);
    /* Light Settings */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    scale = 1;
    red = 0.5;
    green = 0.5;
    blue = 0.5;
    mag = 0;
    mouseHeld = false;
    rotationOK = false;
    translateOK = false;
    cullingOK = false;
    glTranslatef(0,-1,0);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    if(objPtr)
   {
        if (needsReset)
            this->resetView();
        glScaled(scale,scale,scale);
        if (cullingOK)
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }
        else
            glDisable(GL_CULL_FACE);
        if (mouseHeld && rotationOK && !translateOK && (dx!=0 || dy!=0))
        {
            int yRot, xRot;
            xRot = - dx/20;
            yRot = dy/20;
            mag = sqrt(xRot*xRot + yRot* yRot)/100;
            QQuaternion qX = QQuaternion::fromAxisAndAngle(1,0,0,yRot);
            QQuaternion qY = QQuaternion::fromAxisAndAngle(0,1,0,xRot);
            QMatrix4x4 m;
            m.rotate(qX);
            m.rotate(qY);
            glMatrixMode(GL_MODELVIEW);
            QVector3D c(center.at(0), center.at(1), center.at(2));
            glTranslatef(center.at(0), center.at(1), center.at(2));
            glMultMatrixf(m.constData());
            //glRotatef(mag,yRot,xRot,0);
            glTranslatef(-center.at(0), -center.at(1), -center.at(2));
            c = qX.rotatedVector(c);
            c = qY.rotatedVector(c);
            center[0] = c.x();
            center[1] = c.y();
            center[2] = c.z();
        }
        else if (mouseHeld && translateOK && !rotationOK)
        {
            float xT,yT;
            xT = (maxCoords.at(0) - minCoords.at(0))*dx/(10*this->width());
            yT = -(maxCoords.at(1) - minCoords.at(1))*dy/(10*this->height());
            cam.translate(xT,yT);
        }
        glMatrixMode(GL_MODELVIEW);
        drawObject();
   }
}

void GLWidget::resetView(){
    if (needsReset) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float radius = radius + radius/4;
        viewAngle = 10;
        fdist = radius/tan(viewAngle);
        dNear = fdist - radius;
        dFar = fdist + radius;
        glFrustum(-radius, +radius, +radius, -radius, dNear, dFar);
        glTranslatef(-center.at(0), -center.at(1), -center.at(2) - dFar);
        needsReset = false;
   }
}

void GLWidget::drawObject()
{
    if (objPtr){
        glBegin(GL_TRIANGLES);
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
            glColor3f(red,green,blue);
            glNormal3f(normal.at(0), normal.at(1), normal.at(2));
            glVertex3f(v1.X(), v1.Y(), v1.Z());
            glVertex3f(v2.X(), v2.Y(), v2.Z());
            glVertex3f(v3.X(), v3.Y(), v3.Z());
         }
    }
    glEnd();
}

void GLWidget::grabObj(objLoad objFile){
    /* TO DO , CLEAN UP UNUSED OBJFILES */
    objPtr = &objFile;
    vertices = objPtr->getVertices();
    faces = objPtr->getFacets();
    center = objPtr->findCenter();
    radius = objPtr->findRadius();
    maxCoords = objPtr->getMaxCoords();
    minCoords = objPtr->getMinCoords();
    needsReset = true;
}

void GLWidget::grabColor(double r, double g, double b)
{
    red = r/255;
    green = g/255;
    blue = b/255;
}

void GLWidget::resizeGL(int w, int h){

}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
    mouseHeld = true;
    x0 = e->x();
    y0 = e->y();
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
        //std::cout<< dx << " , " << dy << std::endl;
    }
}

void GLWidget::rotateCenter(QQuaternion q)
{
    QVector4D u = q.normalized().toVector4D();
    QVector3D v(center.at(0), center.at(1), center.at(0));
    float s = u.w();
    QVector3D u2 = u.toVector3D();
    QVector3D vprime;
    vprime = 2.0f * QVector3D::dotProduct(u2,v)*u2
            + (QVector3D(s*s, s*s, s*s) - QVector3D::dotProduct(u2,u2)*v)
            + QVector3D(2.0f*s, 2.0f*s, 2.0f*s) * QVector3D::crossProduct(u2,v);
    center[0] = vprime.x();
    center[1] = vprime.y();
    center[2] = vprime.z();
}

bool GLWidget::toggleRotation(){
    dx = 0; dy = 0;
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
    dx = 0; dy = 0;
    if (translateOK)
        translateOK = false;
    else
        translateOK = true;
    return translateOK;
}

double GLWidget::increaseScale()
{
    scale = scale + 0.01;
    return scale;
}

double GLWidget::decreaseScale()
{
    scale = scale - 0.01;
    return scale;
}

void GLWidget::setScale()
{
    scale = 1;
}

static void loadMatrix(const QMatrix4x4& m)
{
    // static to prevent glLoadMatrixf to fail on certain drivers
    static GLfloat mat[16];
    const float *data = m.constData();
    for (int index = 0; index < 16; ++index)
        mat[index] = data[index];
    glLoadMatrixf(mat);
}

