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
    axisOfRotation.setX(0);
    axisOfRotation.setY(0);
    axisOfRotation.setZ(0);
    xAxis.setX(1); xAxis.setY(0); xAxis.setZ(0);
    yAxis.setX(0); yAxis.setY(1); yAxis.setZ(0);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    int xNow = x;
    int yNow = y;
    if(objPtr)
   {
        dx = xNow - prevPos[0];
        dy = yNow - prevPos[1];

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
        if ( mouseHeld && rotationOK && !translateOK && (dx!=0 || dy!=0))
        {
            axisOfRotation.setZ(0);
            if (dx == 0){
                axisOfRotation = xAxis;
            } else if (dy == 0) {
                axisOfRotation = yAxis;
            } else {
                axisOfRotation.setX(dy);
                axisOfRotation.setY(dx);
            }
            mag = sqrt(dx*dx + dy*dy)/5;
            /* Create Rotation Quaternion */
            QQuaternion qR = QQuaternion::fromAxisAndAngle(axisOfRotation, mag);
            /* Create Rotation Matrix */
            QMatrix4x4 m;
            m.rotate(qR);
            /* Try Rotating Axis by Rotation Matrix */
            xAxis = xAxis * m;
            yAxis = yAxis * m;
            glMatrixMode(GL_MODELVIEW);
            glTranslatef(center.at(0), center.at(1), center.at(2));
            /* Multiply Rotation Matrix */
            glMultMatrixf(m.constData());
            glTranslatef(-center.at(0), -center.at(1), -center.at(2));
        }
        else if (mouseHeld && translateOK && !rotationOK)
        {
            float xT,yT;
            /* Adjust Magnitude of Translation to Dimensions of Model */
            xT = (maxCoords.at(0) - minCoords.at(0))*dx/(10*this->width());
            yT = -(maxCoords.at(1) - minCoords.at(1))*dy/(10*this->height());
            cam.translate(xT,yT);
        }
        glMatrixMode(GL_MODELVIEW);
        drawObject();
        drawAxes();
        prevPos[0] = x;
        prevPos[1] = y;
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
        this->resetAxes();
        needsReset = false;
   }
}

void GLWidget::resetAxes()
{
    this->xAxis = QVector3D(1,0,0);
    this->yAxis = QVector3D(0,1,0);
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

void GLWidget::drawAxes()
{
    glBegin(GL_LINES);
    glLineWidth(100);
    /* Red X Axis */
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(2,0,0);
    /* Green Y Axis */
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,2,0);
    /* Blue Z Axis */
    glColor3f(0,0,2);
    glVertex3f(0,0,0);
    glVertex3f(0,0,2);
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
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mouseHeld = false;
    x0 = 0;
    y0 = 0;
    dx = 0;
    dy = 0;
}

void GLWidget::mouseMoveEvent(QMouseEvent *e){
    this->x = e->x();
    this->y = e->y();
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

