#include "glwidget.h"
#include "model.h"
model::model()
{

}

model::model(objLoad<HDS> objFile) {
    objPtr = &objFile;

    polyhedron.delegate(objFile);
    Poly_copy polyhedron_copy_modifier(polyhedron);
    //poly2.delegate(objFile);
    mesh.delegate(polyhedron_copy_modifier);
    //nefPoly = Nef_Polyhedron(polyhedron);
    m_center = objPtr->findCenter();
    m_radius = objPtr->findRadius();
    maxCoords = objPtr->getMaxCoords();
    minCoords = objPtr->getMinCoords();
    red = 0.75;
    green = 0.75;
    blue = 0.75;
    currTrans.assign(2,0);
    this->computeNormals();
    Vector vec(0.0,0.0,1.0);
    Point a(-0.2, 0.2, -0.2);
    Plane plane_query(a,vec);
    this->seekIntersections(plane_query, polyhedron);
    hasVol = false;
    volumeMode = false;
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

void model::seekIntersections(Plane plane_query, Polyhedron _polyhedron)
{

    Tree tree(faces(_polyhedron).first, faces(_polyhedron).second, _polyhedron);
    Plane_intersection plane_intersection = tree.any_intersection(plane_query);
    if(plane_intersection)
    {
      if(boost::get<Segment>(&(plane_intersection->first)))
            std::cout << "intersection object is a segment" << std::endl;
    }
    /************************************************************/
    tree.all_intersections(plane_query,std::back_inserter(intersections));

    //Segment segment;
    //Here, I get intersetions (Points: (X,Y,Z))
    //for( it = intersections.begin();it !=intersections.end();it++) {
       // std::cout<< it << std::endl; //m_segment.push_back(segment);
    //}
}

Polyhedron model::volumePolyhedron()
{
    polyhedron_builder<HDS> builder(c3t3);
    vol_poly.delegate(builder);

    return vol_poly;
}



void model::drawMe() {
   if(volumeMode)
       this->drawPoly(vol_poly);
   else
       this->drawPoly(polyhedron);
}

void model::drawPoly(Polyhedron poly) {
    glBegin(GL_TRIANGLES);
    glColor3f(red, green, blue);
    for (Polyhedron::Facet_const_iterator faceIter = poly.facets_begin(); faceIter != poly.facets_end(); ++faceIter) {
        std::cout << &faceIter;
        drawTriangle(faceIter);
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
        this->volumePolyhedron();
        hasVol = true;
        volumeMode = true;
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

void model::setColor(double r, double g, double b)
{
    red = r;
    blue = b;
    green = g;
}

bool model::hasVolume() {
    return hasVol;
}

bool model::toggleMode() {
    if (hasVol)
        volumeMode = volumeMode;
    else
        volumeMode = false;
}
