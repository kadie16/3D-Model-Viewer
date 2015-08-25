#include "glwidget.h"
#include "model.h"

model::model()
{

}

model::model(float x, float y, float dx, float dy)
{
   Polyhedron p;
   Point p1(x,y,0);
   Point p2(x+dx, y, 0);
   Point p3(x+dx, y+dy, 0);
   Point p4(x, y+dy, 0);
   surface_poly.make_triangle(p1,p2,p3);
   surface_poly.make_triangle(p2,p3,p4);
   m_center.push_back(x+dx/2);
   m_center.push_back(y+dy/2);
   m_radius = sqrt(dx*dx + dy*dy);
   maxCoords.push_back((x > x + dx)?x:x+dx);
   maxCoords.push_back((y > y + dy)?y:y+dy);
   minCoords.push_back((x < x + dx)?x:x+dx);
   minCoords.push_back((y > y + dy)?y:y+dy);
   red = 0.0f;
   green = 0.0f;
   blue = 0.75f;
   currTrans.assign(2,0);
   surface_poly = computeNormals(surface_poly);
   isPlane = true;
   hasVol = false;
   volumeMode = false;
}

model::model(objLoad<HDS> objFile) {
    objPtr = &objFile;
    surface_poly.delegate(objFile);
    Poly_copy polyhedron_copy_modifier(surface_poly);
    //poly2.delegate(objFile);
    mesh.delegate(polyhedron_copy_modifier);
    m_center = objPtr->findCenter();
    m_radius = objPtr->findRadius();
    maxCoords = objPtr->getMaxCoords();
    minCoords = objPtr->getMinCoords();
    red = 0.75f;
    green = 0.75f;
    blue = 0.75f;
    currTrans.assign(2,0);
    surface_poly = computeNormals(surface_poly);
    Vector vec(0.0,0.0,1.0);
    Point a(-0.2, 0.2, -0.2);
    Plane plane_query(a,vec);
    surface_triMap = makeMap(surface_poly);
    hasVol = false;
    volumeMode = false;
}

Polyhedron model::computeNormals(Polyhedron poly)
{
    std::for_each(poly.facets_begin(), poly.facets_end(), Facet_normal());
    std::for_each(poly.vertices_begin(), poly.vertices_end(), Vertex_normal());
    return poly;
}

Polyhedron model::poly()
{
    return surface_poly;
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

void model::seekIntersections(Plane plane_query)
{
    if (!isPlane) {
        this->clearIntersections();
        Polyhedron* _polyhedron;
        if (volumeMode){
            std::cout << "volume intersections" << std::endl;
            _polyhedron = &volume_poly;
        }
        else {
            _polyhedron = &surface_poly;
        }
        Tree tree(faces(*_polyhedron).first, faces(*_polyhedron).second, *_polyhedron);
        tree.all_intersections(plane_query,std::back_inserter(intersections));
        this->drawIntersections();
    }
}

Tri_Pair model::triPair(CGAL::Triangle_3<Kernel> tri) {
    return Tri_Pair(tri, CGAL::normal(tri.vertex(2), tri.vertex(1), tri.vertex(3)));
}

void model::seekIntersections2(Plane plane_query)
{
    if (!isPlane) {
        intersections2.clear();
        for(int i=0; i < surface_triMap.size(); i++) {
            /* If the triangle intersects the plane */
            if (CGAL::do_intersect(plane_query, surface_triMap[i])) {
                intersections2.push_back(triPair(surface_triMap[i]));
            }
        }
    }
}


void model::seekIntersections3(Plane plane_query)
{
    if (!isPlane) {
        intersections3.clear();
        std::vector<CGAL::Triangle_3<Kernel> > cell;
        for (int i=0; i < volume_triMap.size(); i++) {
            cell = volume_triMap[i];
            for (int k = 0; k < 4; k++) {
                if (CGAL::do_intersect(plane_query, cell[k])) {
                    /* save this cell and stop checking it*/
                    intersections3.push_back(triPair(cell[0]));
                    intersections3.push_back(triPair(cell[1]));
                    intersections3.push_back(triPair(cell[2]));
                    intersections3.push_back(triPair(cell[3]));
                    break;
                }
            }
        }
    }
}

void model::drawIntersections2() {
    std::vector<std::pair<CGAL::Triangle_3<Kernel>,CGAL::Vector_3<Kernel> > >* currentIntersections;
    CGAL::Vector_3<Kernel>* n;
    if(volumeMode) {
        currentIntersections = &intersections3;
        glColor3f(0,0,1);
    } else {
        currentIntersections = &intersections2;
        glColor3f(1,0,0);
    }
    Point p1,p2,p3;
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < currentIntersections->size(); i++) {
        p1 = currentIntersections->at(i).first.vertex(0);
        p2 = currentIntersections->at(i).first.vertex(1);
        p3 = currentIntersections->at(i).first.vertex(2);
        n =  &currentIntersections->at(i).second;
       // glColor3f(1,0,0);
        glNormal3f(n->hx(), n->hy(), n->hz());
        drawTriangle(p1,p2,p3);
    }
    glEnd();
}

void model::drawIntersections()
{
    for (std::list<Plane_intersection>::iterator it = intersections.begin();it !=intersections.end(); it++) {
        Plane_intersection p = *it;
        //std::cout << "first: " << (p->first) << std::endl;
        if(boost::get<Segment>(&(p->first))) {
            //drawTriangle((p->second));
            //std::cout << "Segment" << p->second->hx() << std::endl;
                glLineWidth(4);
                glBegin(GL_LINES);
                glColor3f(1,0,0);
                Point p1 = boost::get<Segment>(&(p->first))->point(0); //vertex(0);
                Point p2 = boost::get<Segment>(&(p->first))->point(1);
                glVertex3f(p1.hx(), p1.hy(), p1.hz());
                glVertex3f(p2.hx(), p2.hy(), p2.hz());
                glEnd();
        } else if (boost::get<Point>(&(p->first))) {
           /* std::cout<< "Triangle" << std::endl;
            Point p1 = boost::get<Triangle>(&(p->first))->vertex(0);
            Point p2 = boost::get<Triangle>(&(p->first))->vertex(1);
            Point p3 = boost::get<Triangle>(&(p->first))->vertex(3);

            glBegin(GL_TRIANGLES);
            glColor3f(1,0,0);
            drawTriangle(p1,p2,p3);
            glEnd(); */
        } else {
            std::cout << "Other" << std::endl;
        }
    }
}

void model::clearIntersections()
{
    intersections.clear();
}

std::vector<CGAL::Triangle_3<Kernel> > model::makeMap(Polyhedron poly)
{
    std::vector<CGAL::Triangle_3<Kernel> > triMap;
    int i = 0;
    for (Polyhedron::Facet_const_iterator faceIter = poly.facets_begin(); faceIter != poly.facets_end(); ++faceIter) {
        triMap.push_back(makeTriangle(faceIter));
    }
    return triMap;
}

std::vector<std::vector<CGAL::Triangle_3<Kernel> > > model::makeMap(C3T3 c3t3)
{
    std::vector<std::vector<CGAL::Triangle_3<Kernel> > > toReturn;
    std::vector<CGAL::Triangle_3<Kernel> > temp;
    Tr t = c3t3.triangulation();
    for (Tr::Finite_cells_iterator fIt = t.finite_cells_begin(); fIt != t.finite_cells_end(); ++fIt) {
        temp = makeCellVec(*fIt);
        toReturn.push_back(temp);
    }
    return toReturn;
}

Polyhedron model::volumePolyhedron()
{
    polyhedron_builder<HDS> builder(c3t3);
    volume_poly.delegate(builder);
    volume_poly = computeNormals(volume_poly);
    return volume_poly;
}



void model::drawMe() {
   if(volumeMode)
       this->drawPoly(volume_poly);
   else
       this->drawPoly(surface_poly);
}

void model::drawPoly(Polyhedron poly) {
    glBegin(GL_TRIANGLES);
    glColor3f(red, green, blue);
    for (Polyhedron::Facet_const_iterator faceIter = poly.facets_begin(); faceIter != poly.facets_end(); ++faceIter) {
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

CGAL::Triangle_3<Kernel> model::makeTriangle(Polyhedron::Facet_const_handle f)
{

    CGAL::Point_3<Kernel> p1,p2,p3,p4;
    Polyhedron::Halfedge_const_handle h;
    h = f->halfedge();
    p1 = h->vertex()->point();
    p2 = h->next()->vertex()->point();
    p3 = h->prev()->vertex()->point();
    return Kernel::Triangle_3(p1,p2,p3);
}

std::vector<CGAL::Triangle_3<Kernel> > model::makeCellVec(Tr::Cell c)
{
    Point p1,p2,p3,p4;
    p1 = c.vertex(0)->point();
    p2 = c.vertex(1)->point();
    p3 = c.vertex(2)->point();
    p4 = c.vertex(3)->point();

    std::vector<CGAL::Triangle_3<Kernel> > toReturn;
    toReturn.push_back(CGAL::Triangle_3<Kernel>(p1,p3,p2));
    toReturn.push_back(CGAL::Triangle_3<Kernel>(p1,p2,p4));
    toReturn.push_back(CGAL::Triangle_3<Kernel>(p1,p4,p3));
    toReturn.push_back(CGAL::Triangle_3<Kernel>(p2,p3,p4));

    return toReturn;
}

bool model::generateVolumeMesh()
{
    using namespace CGAL::parameters;
    //Feature_Mesh_Domain f_domain(mesh);
    //f_domain.detect_features();
    Mesh_Domain domain(surface_poly);
    //Feature_Mesh_Criteria criteria(facet_angle=30, facet_size=0.1, facet_distance=0.025,cell_radius_edge_ratio=2, cell_size=0.1);
    Mesh_Criteria criteria(facet_angle=30, facet_size=0.1, facet_distance=0.025,
                           cell_radius_edge_ratio=2, cell_size=0.1);
    try {
        //Feature_C3T3 f_c3t3 = CGAL::make_mesh_3<Feature_C3T3>(f_domain, criteria);
        c3t3 = CGAL::make_mesh_3<C3T3>(domain, criteria);
        this->volumePolyhedron();
        volume_triMap = makeMap(c3t3);
        hasVol = true;
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
    for (Tr::Finite_cells_iterator fIt = t.finite_cells_begin(); fIt != t.finite_cells_end(); ++fIt) {
        p1 = fIt->vertex(0)->point();
        p2 = fIt->vertex(1)->point();
        p3 = fIt->vertex(2)->point();
        p4 = fIt->vertex(3)->point();
        CGAL::Vector_3<Kernel> n = CGAL::normal(p1,p3,p2);
        glNormal3f(n.hx(), n.hy(), n.hz());
        drawTriangle(p1,p3,p2);
        n = CGAL::normal(p1,p2,p4);
        glNormal3f(n.hx(), n.hy(), n.hz());
        drawTriangle(p1,p2,p4);
        n = CGAL::normal(p1,p4,p3);
        glNormal3f(n.hx(), n.hy(), n.hz());
        drawTriangle(p1,p4,p3);
        n = CGAL::normal(p2,p3,p4);
        glNormal3f(n.hx(), n.hy(), n.hz());
        drawTriangle(p2,p3,p4);

    }
    glEnd();
}

void model::drawTriangle(Point p1, Point p2, Point p3) {

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
        volumeMode = !volumeMode;
    else
        volumeMode = false;
    return volumeMode;
}
