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
    modelCenter = objPtr->findCenter();
    radius = objPtr->findRadius();
    maxCoords = objPtr->getMaxCoords();
    minCoords = objPtr->getMinCoords();
    computeNormals();
}

void model::computeNormals()
{
    std::for_each(polyhedron.facets_begin(), polyhedron.facets_end(), Facet_normal());
    std::for_each(polyhedron.vertices_begin(), polyhedron.vertices_end(), Vertex_normal());
    std::cout<< "normals computed" << std::endl;
}

Polyhedron model::poly()
{
    return polyhedron;
}

std::vector<float> model::center()
{
    return modelCenter;
}

void model::drawMe()
{
    std::cout<< "in drawMe" << std::endl;
    glBegin(GL_TRIANGLES);
    glColor3f(red, green, blue);
    int i = 0;
    for (Polyhedron::Facet_const_iterator faceIter = polyhedron.facets_begin(); faceIter != polyhedron.facets_end(); ++faceIter) {
        // if (faceIter->is_triangle())
        std::cout<< i++ << std::endl;
        GLWidget::drawTriangle(faceIter);
         //else if (faceIter->is_quad())
         //      drawQuad(faceIter);
    }
    glEnd();
}

