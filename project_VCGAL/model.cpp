#include "glwidget.h"
#include "model.h"

model::model()
{

}

model::model(objLoad<HDS> objFile)
{
    objPtr = &objFile;
    polyhedron.delegate(objFile);
    Poly_copy polyhedron_copy_modifier(polyhedron);
    mesh.delegate(polyhedron_copy_modifier);
    m_center = objPtr->findCenter();
    m_radius = objPtr->findRadius();
    maxCoords = objPtr->getMaxCoords();
    minCoords = objPtr->getMinCoords();
    red = 0.75;
    green = 0.75;
    blue = 0.75;
    currTrans.assign(2,0);
    this->computeNormals();
}

void model::setRotation(QQuaternion newQ)
{
    this->currQ = newQ;
    std::cout << currQ.x() << " , " << currQ.y() << " , " << currQ.z() << std::endl;
}

void model::computeNormals()
{
    std::for_each(polyhedron.facets_begin(), polyhedron.facets_end(), Facet_normal());
    std::for_each(polyhedron.vertices_begin(), polyhedron.vertices_end(), Vertex_normal());
}

Polyhedron model::poly()
{
    return polyhedron;
}

std::vector<float> model::center()
{
    return m_center;
}

float model::radius()
{
    return m_radius;
}

std::vector<float> model::max()
{
    return maxCoords;
}

std::vector<float> model::min() {
    return minCoords;
}

float model::getTransX() {
    return currTrans.at(0);
}

float model::getTransY() {
    return currTrans.at(1);
}

QQuaternion model::getRotation()
{
    return currQ;
}

void model::setTransX(float f) {
    currTrans[0] = f;
}

void model::setTransY(float f) {
    currTrans[1] = f;
}

void model::translate(float xT, float yT)
{
    currTrans[0] = currTrans[0] + xT;
    currTrans[1] = currTrans[1] + yT;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(currTrans[0], currTrans[1], 0);
    this->moveToCenter();
}

void model::moveToCenter()
{
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-m_center.at(0), -m_center.at(1), -m_center.at(2));
}

void model::setColor(double r, double g, double b)
{
    red = r;
    blue = b;
    green = g;
}
QQuaternion model::getCurrQ() const
{
    return currQ;
}

void model::setCurrQ(const QQuaternion &value)
{
    currQ = value;
}


void model::drawMe() {
    glBegin(GL_TRIANGLES);
    glColor3f(red, green, blue);
    for (Polyhedron::Facet_const_iterator faceIter = polyhedron.facets_begin(); faceIter != polyhedron.facets_end(); ++faceIter) {
        // if (faceIter->is_triangle())
        drawTriangle(faceIter);
         //else if (faceIter->is_quad())
         //      drawQuad(faceIter);
    }
    glEnd();
}

void model::drawTriangle(Polyhedron::Facet_const_handle f)
{
    CGAL::Vector_3<Kernel> n1, n2, n3;
    CGAL::Point_3<Kernel> p1,p2,p3,p4;
    Polyhedron::Halfedge_const_handle h;
    h = f->halfedge();
    n1 = h->vertex()->normal();
    n2 = h->next()->vertex()->normal();
    n3 = h->prev()->vertex()->normal();
    p1 = h->vertex()->point();
    p2 = h->next()->vertex()->point();
    p3 = h->prev()->vertex()->point();
    glNormal3f(n1.hx(), n1.hy(), n1.hz());
    glVertex3f(p1.hx(), p1.hy(), p1.hz());
    glNormal3f(n2.hx(), n2.hy(), n2.hz());
    glVertex3f(p2.hx(), p2.hy(), p2.hz());
    glNormal3f(n3.hx(), n3.hy(), n3.hz());
    glVertex3f(p3.hx(), p3.hy(), p3.hz());
}

bool model::generateVolumeMesh()
{
    using namespace CGAL::parameters;
    Mesh_Domain domain(polyhedron);
    Mesh_Criteria criteria(facet_angle=30, facet_size=0.1, facet_distance=0.025,
                          cell_radius_edge_ratio=2, cell_size=0.1);
    try {
        c3t3 = CGAL::make_mesh_3<C3T3>(domain, criteria);
    } catch (...) {
        return false;
    }
    return true;
}

void model::drawVolume()
{
    CGAL::Point_3<Kernel> p1,p2,p3,p4;
    Tr t;
    t = c3t3.triangulation();
    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    for (Tr::Finite_cells_iterator fIt = t.finite_cells_begin(); fIt != t.finite_cells_end(); ++fIt) {
        p1 = fIt->vertex(0)->point();
        p2 = fIt->vertex(1)->point();
        p3 = fIt->vertex(2)->point();
        p4 = fIt->vertex(3)->point();
        CGAL::Vector_3<Kernel> n = CGAL::normal(p1,p2,p3);
        glNormal3f(n.hx(), n.hy(), n.hz());
        drawTriangle(p1,p2,p3);
        n = CGAL::normal(p1,p3,p4);
        glNormal3f(n.hx(), n.hy(), n.hz());
        drawTriangle(p1,p3,p4);
        n = CGAL::normal(p1,p4,p2);
        glNormal3f(n.hx(), n.hy(), n.hz());
        drawTriangle(p1,p2,p4);
        n = CGAL::normal(p2,p4,p3);
        glNormal3f(n.hx(), n.hy(), n.hz());
        drawTriangle(p2,p4,p3);

    }
    glEnd();
}

void model::drawTriangle(Point p1, Point p2, Point p3)
{
    glVertex3f(p1.hx(), p1.hy(), p1.hz());
    glVertex3f(p2.hx(), p2.hy(), p2.hz());
    glVertex3f(p3.hx(), p3.hy(), p3.hz());
}

