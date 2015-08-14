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
    center = objPtr->findCenter();
    radius = objPtr->findRadius();
    maxCoords = objPtr->getMaxCoords();
    minCoords = objPtr->getMinCoords();
    computeNormals();
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

