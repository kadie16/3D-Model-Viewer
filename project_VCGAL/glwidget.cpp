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
    cam.setAspect(w0,h0);
    axisOfRotation.setX(0);
    axisOfRotation.setY(0);
    axisOfRotation.setZ(0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
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
        glMatrixMode(GL_PROJECTION);
        glScaled(scale,scale,scale);
        glMatrixMode(GL_MODELVIEW);
        /* CULLING */
        if (cullingOK)
        {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }
        else
            glDisable(GL_CULL_FACE);
        /* ROTATION */
        if (mouseHeld && rotationOK && !translateOK && (dx!=0 || dy!=0))
        {
            this->drag2Rotate(dx,dy);
        }
        /* TRANSLATION */
        else if (mouseHeld && translateOK && !rotationOK)
        {
            this->drag2Translate(dx, dy);
        }
        /* ZOOM */
        else if (mouseHeld && zoomOK) {
            this->drag2Zoom(dy);
        }
        /* Apply Current Settings */
        m.rotate(currQ);
        glMatrixMode(GL_PROJECTION);
        cam.setZoom(zoomF);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
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
        zoomF = cam.fitModel(maxCoords.at(0), minCoords.at(0),
                     maxCoords.at(1), minCoords.at(1),
                     maxCoords.at(2), minCoords.at(2));
        needsReset = false;
   }
}

void GLWidget::drawObject()
{
    glBegin(GL_TRIANGLES);
    glColor3f(red, green, blue);
    for (Polyhedron::Facet_const_iterator faceIter = mesh.facets_begin(); faceIter != mesh.facets_end(); ++faceIter) {
        // if (faceIter->is_triangle())
            drawTriangle(faceIter);
         //else if (faceIter->is_quad())
         //      drawQuad(faceIter);
    }
    glEnd();
}

void GLWidget::drawTriangle(Polyhedron::Facet_const_handle f)
{
    Polyhedron::Halfedge_const_handle h = f->halfedge();
    CGAL::Point_3<Kernel> p1,p2,p3;
    p1 = h->vertex()->point();
    p2 = h->next()->vertex()->point();
    p3 = h->prev()->vertex()->point();
    CGAL::Vector_3<Kernel> n = normals[f];
    glNormal3f(n.hx(), n.hy(), n.hz());
    glVertex3f(p1.hx(), p1.hy(), p1.hz());
    glVertex3f(p2.hx(), p2.hy(), p2.hz());
    glVertex3f(p3.hx(), p3.hy(), p3.hz());
}

void GLWidget::drawQuad(Polyhedron::Facet_const_handle f)
{
   /* CGAL::Point_3<Kernel> p1,p2,p3,p4;
    p1 = circulator->vertex()->point();
    ++circulator;
    p2 = circulator->vertex()->point();
    ++circulator;
    p3 = circulator->vertex()->point();
    ++circulator;
    p4 = circulator->vertex()->point();
    CGAL::Vector_3<Kernel> normal = CGAL::normal(p2, p1, p3);
    glBegin(GL_QUADS);
    glColor3f(red, green, blue);
    glNormal3f(normal.hx(), normal.hy(), normal.hz());
    glVertex3f(p1.hx(), p1.hy(), p1.hz());
    glVertex3f(p2.hx(), p2.hy(), p2.hz());
    glVertex3f(p3.hx(), p3.hy(), p3.hz());
    glVertex3f(p4.hx(), p4.hy(), p4.hz()); */
}

void GLWidget::computeNormals()
{
    for (Polyhedron::Facet_const_iterator faceIter = mesh.facets_begin(); faceIter != mesh.facets_end(); ++faceIter) {
         Polyhedron::Halfedge_const_handle h = faceIter->halfedge();
         CGAL::Point_3<Kernel> p1,p2,p3;
         p1 = h->vertex()->point();
         p2 = h->next()->vertex()->point();
         p3 = h->prev()->vertex()->point();
         normals[faceIter] = CGAL::normal(p2,p1,p3);
    }
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

void GLWidget::grabObj(objLoad<HDS> objFile){
    /* TO DO , CLEAN UP UNUSED OBJFILES */
    objPtr = &objFile;
    mesh.delegate(objFile);
    center = objPtr->findCenter();
    radius = objPtr->findRadius();
    maxCoords = objPtr->getMaxCoords();
    minCoords = objPtr->getMinCoords();
    computeNormals();
    cam.findModel(objPtr);
    cam.adjustAspect(this->width(), this->height());
    needsReset = true;
}

void GLWidget::grabColor(double r, double g, double b)
{
    red = r/255;
    green = g/255;
    blue = b/255;
}

void GLWidget::resizeGL(int w, int h){
    cam.adjustAspect(w,h);
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

QQuaternion GLWidget::drag2Rotate(float dx, float dy)
{
    /* Define Axis of Rotation */
    axisOfRotation.setX(-dy);
    axisOfRotation.setY(-dx);
    axisOfRotation.setZ(0);
    mag = sqrt(dx*dx + dy*dy);
    /* Update Rotation Quaternion */
    QQuaternion newQ = QQuaternion::fromAxisAndAngle(axisOfRotation, mag);
    currQ = newQ * currQ;
    return currQ;
}

void GLWidget::drag2Translate(float dx, float dy)
{
    float xT,yT;
    /* Adjust Magnitude of Translation to Dimensions of Model */
    xT = (maxCoords.at(0) - minCoords.at(0))*dx/(scale*1*this->width());
    yT = -(maxCoords.at(1) - minCoords.at(1))*dy/(scale*1*this->height());
    cam.translate(xT,yT);
}

void GLWidget::drag2Zoom(float dy)
{
    zoomF = zoomF + dy/100.0;
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


