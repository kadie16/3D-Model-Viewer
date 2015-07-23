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
    zoomF = 1;
    scale = 1;
    radius = 0;
    red = 0.75;
    green = 0.75;
    blue = 0.75;
    mag = 0;
    mouseHeld = false;
    rotationOK = false;
    translateOK = false;
    needsReset = false;
    cullingOK = false;
    w0 = this->width();
    h0 = this->height();
    axisOfRotation.setX(0);
    axisOfRotation.setY(0);
    axisOfRotation.setZ(0);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    int xNow = x;
    int yNow = y;
    /* If a File is Loaded*/
    if(objPtr)
   {
        dx = (xNow - prevPos[0])/2;
        dy = (yNow - prevPos[1])/2;
        QMatrix4x4 m;
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
            /* Define Axis of Rotation */
            axisOfRotation.setX(-dy);
            axisOfRotation.setY(-dx);
            axisOfRotation.setZ(0);
            mag = sqrt(dx*dx + dy*dy);
            /* Update Rotation Quaternion */
            QQuaternion newQ = QQuaternion::fromAxisAndAngle(axisOfRotation, mag);
            currQ = newQ * currQ;
        }
        else if (mouseHeld && translateOK && !rotationOK)
        {
            float xT,yT;
            /* Adjust Magnitude of Translation to Dimensions of Model */
            xT = (maxCoords.at(0) - minCoords.at(0))*dx/(scale*1*this->width());
            yT = -(maxCoords.at(1) - minCoords.at(1))*dy/(scale*1*this->height());
            cam.translate(xT,yT);
        } else if (mouseHeld && zoomOK) {
            zoomF = zoomF + dy/100.0;
        }
        /* Apply Current Rotation */
        this->adjustViewPort();
        m.rotate(currQ);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        /* ZOOM!!!! */
        cam.setZoom(.6);
        /* Translate so rotation occurs about model center */
        glTranslatef(center.at(0), center.at(1), center.at(2));
        glMultMatrixf(m.constData());
        glTranslatef(-center.at(0), -center.at(1), -center.at(2));
        drawObject();
        drawAxes();
        /* Revert to Original Matrix for Future Transformations */
        glPopMatrix();
        prevPos[0] = xNow;
        prevPos[1] = yNow;
   }
}

void GLWidget::resetView()
{
    if (needsReset) {
        currQ.setScalar(1);
        currQ.setX(0);
        currQ.setY(0);
        currQ.setZ(0);
        cam.viewModel();
        cam.moveToCenter();
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

void GLWidget::drawAxes()
{
    glLineWidth(2);
    glBegin(GL_LINES);
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
    cam.findModel(objPtr);
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
    this->x = e->x();
    this->y = e->y();
    if (e->button() == Qt::LeftButton && !translateOK)
    {
        zoomOK = false;
        rotationOK = true;
    }
    else if (e->button() == Qt::RightButton)
    {
        rotationOK = false;
        translateOK = false;
        zoomOK = true;
    }
    mouseHeld = true;
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    this->x = e->x();
    this->y = e->y();
    rotationOK = false;
    mouseHeld = false;
}

void GLWidget::mouseMoveEvent(QMouseEvent *e){
    this->x = e->x();
    this->y = e->y();
}

void GLWidget::adjustViewPort()
{
    /* Original Aspect */
    float aspect = w0/h0;
    /* Screen Width and Height */
    int sW = this->width()*2;
    int sH = this->height()*2;
    /* Fixed ViewPort Width and Height */
    float vW = sW;
    float vH = sW/aspect;
    if (vW > sH) {
        vH = sH;
        vW = vH * aspect;
    }
    /* Coordinates of Lower Left Corner of ViewPort */
    int vpX = (sW - vW)/2;
    int vpY = (sH - vH)/2;
    glViewport(vpX,vpY,vW,vH);
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


