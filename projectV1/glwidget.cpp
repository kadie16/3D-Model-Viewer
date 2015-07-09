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
        Vertex f;
        //Face actualF();
        std::vector<float> normal;

        Vertex v1, v2, v3;
        //std::cout << vertices.at(0).getX() << " " << vertices.at(0).getY() << " " << vertices.at(0).getZ() << std::endl;

            for (unsigned i = 0 ; i < faces.size() ; i++)
            {
                /* x, y, z in face f are the indices of the vertices that make that face */
                /***************************** CHECK ORDER  ***********************************/
                f = faces.at(i);
                v1 = vertices.at(f.getX() - 1);
                v2 = vertices.at(f.getY() - 1);
                v3 = vertices.at(f.getZ() - 1);
                /* find normals */
                /***************************** CHECK ORDER  ***********************************/
                normal = v1.findNormal(v2, v3);
                v2.inheritNormal(v1);
                v3.inheritNormal(v1);

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
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);

}
