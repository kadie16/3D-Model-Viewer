#include "glwidget.h"
#include "model.h"
#include "vbovertex.h"
model::model()
{

}

model::~model()
{
    /* am making a copy of model, need to find where and stop */
    //if (_vboID != 0)
        //glDeleteBuffers(1, &_vboID);
}

model::model(objLoad<HDS> objFile)
{
    hasVolume = false;
    objPtr = &objFile;
    polyhedron.delegate(objFile);
    Poly_copy polyhedron_copy_modifier(polyhedron);
    numFaces = polyhedron.size_of_facets();
    mesh.delegate(polyhedron_copy_modifier);
    m_center = objPtr->findCenter();
    m_radius = objPtr->findRadius();
    maxCoords = objPtr->getMaxCoords();
    minCoords = objPtr->getMinCoords();
    red = 192;
    green = 192;
    blue = 192;
    currTrans.assign(2,0);
    _vboID = 0;
    this->computeNormals();
    this->genBuffers();
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

void model::genBuffers()
{
   // if (_vboID == 0){
        std::cout<< "Errors at begining:  " << CheckGLErrors() <<std::endl;
        glGenBuffers(1, &_vboID);
        std::cout<< "vbo: " << _vboID << std::endl;
        std::cout<< "Errors after gen: " << CheckGLErrors() <<std::endl;
        std::cout<< numFaces << std::endl;
        vboVertex vertexData[numFaces*3]; // numFaces * 3 vertices per face * 3 dimensions per vertex
        /* fill */
        int i = 0;
        Polyhedron::Halfedge_const_handle h;
        CGAL::Point_3<Kernel> p[3];
        CGAL::Vector_3<Kernel> n[3];

        for (Polyhedron::Facet_const_iterator faceIter = polyhedron.facets_begin(); faceIter != polyhedron.facets_end(); ++faceIter) {

            h = faceIter->halfedge();
            p[0] = h->vertex()->point();
            n[0] = h->vertex()->normal();
            p[1] = h->next()->vertex()->point();
            n[1] = h->next()->vertex()->normal();
            p[2] = h->prev()->vertex()->point();
            n[2] = h->prev()->vertex()->normal();
            for (int k = 0; k < 3; k++){
                vertexData[i].position.x = p[k].hx();
                vertexData[i].position.y = p[k].hy();
                vertexData[i].position.z = p[k].hz();
                vertexData[i].normal.x = n[k].hx();
                vertexData[i].normal.y = n[k].hy();
                vertexData[i].normal.z = n[k].hz();
                vertexData[i].color.r = red;
                vertexData[i].color.g = green;
                vertexData[i].color.b = blue;
                vertexData[i].color.a = 1;
                i++;
            }
        }
        std::cout << red  << " " << green << " " <<
                       blue  << std::endl;
        i = 0;
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind Buffer
    //}
}

void model::setColor(GLubyte r, GLubyte g, GLubyte b)
{
    red = r;
    green = g;
    blue = b;
    this->genBuffers();
}

void model::drawMe() {

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glEnableVertexAttribArray(0);
    /* This is the position attribute pointer */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vboVertex), (void*)offsetof(vboVertex, position));
    /* This is the color attribute pointer */
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vboVertex), (void*)offsetof(vboVertex, color));
    /* This is the normal attribute pointer */
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vboVertex), (void*)offsetof(vboVertex, normal));
    glDrawArrays(GL_TRIANGLES, 0, numFaces*3);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /*
    glBegin(GL_TRIANGLES);
    glColor3f(red, green, blue);
    for (Polyhedron::Facet_const_iterator faceIter = polyhedron.facets_begin(); faceIter != polyhedron.facets_end(); ++faceIter) {
        // if (faceIter->is_triangle())
        drawTriangle(faceIter);
         //else if (faceIter->is_quad())
         //      drawQuad(faceIter);
    }
    glEnd(); */
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
        hasVolume = true;
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


