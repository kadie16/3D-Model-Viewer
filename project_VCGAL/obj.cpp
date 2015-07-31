#include "obj.h"

using namespace std;

obj::obj()
{

}

void obj::build(string fName)
{
    CGAL::Polyhedron_incremental_builder_3<HDS> builder(hds, true);
    typedef typename HDS::Vertex   Vertex;
    typedef typename Vertex::Point Point;
    B.begin_surface(0,0,0);
    maxCoords.assign(3, 0);
    minCoords.assign(3,0);
    center.assign(3,0);
    cout << "Loading object from path:  " << fName << endl;
    fileName = fName;
    /* Open file stream */
    ifstream stream(fName.c_str());
    if (stream.is_open())
    {
        string currLine;
        while (!stream.eof())
        {
            /* Get next line of file */
            getline(stream, currLine);
            if (currLine.size() > 2) {
                /* Determine whether it is a vertex, normal, or face line */
                if (currLine[0] == 'v' && currLine[1] == ' ') {
                    Vertex newV = this->parseVertex(currLine);
                    builder.add_vertex(newV);
                    this->checkMax(newV);
                    this->checkMin(newV);
                 } else if (currLine[0] == 'v' && currLine[1] == 'n') {
                    Vertex n(currLine, currLine[1]);
                    normals.push_back(n);
                } else if (currLine[0] == 'f' && currLine[1] == ' ') {
                    builder.begin_facet();
                    vector<Vertex> v = this->parseFace(currLine);
                    builder.add_vertex_to_facet(v.at(0));
                    builder.add_vertex_to_facet(v.at(1));
                    builder.add_vertex_to_facet(v.at(2));
                    if (v.size() > 3)
                        builder.add_vertex_to_facet(v.at(3));
                    builder.end_facet();
                }
            }
        }
        poly.delegate(builder);
        stream.close();
    } else
    {
        cout << "File load failed!" << endl;
    }
}

string obj::getFileName()
{
    return fileName;
}

void obj::print()
{
    cout << fileName << " vertices: " << endl;
    CGAL::Polyhedron_3::Vertex_iterator vIter = this->getVertices();
    for ( vIter ; vIter != poly.vertices_end() ; vIter++ ) {
       std::cout << poly.vertex(vIter) << std::endl;
    }
    CGAL::Polyhedron_3::Facet_iterator fIter = this->getFacets();
    for (fIter; fIter != poly.facets_end() ; fIter++) {
        std::cout << poly.facet(fIter) << std::endl;
    }

}

typename Polyhedron::Vertex_iterator obj::getVertices()
{
    return poly.vertices_begin();
}

typename Polyhedron::Facet_iterator obj::getFacets()
{
    return poly.facets_begin();
}

vector<int> obj::parseFace(string input){
    vector<int> toReturn;
    /* Parses differently, depending on if there are slashes in line */
    if (input.find("/") != string::npos) {
        /* remove the "f" in front of the line */
        input.erase(0,1);
        string delimiter = "/";
        size_t pos = 0;
        string token;
        string token2;
        int index;
        int prevIndex = 0;
        while ((pos = input.find(delimiter) != string::npos)) {
         /* Token is index of vertex in the face */
         token = input.substr(0, input.find(delimiter));
         istringstream(token) >> index; /* Only succeeds if token is an integer */
         if (index != prevIndex){
            toReturn.push_back(index);
            prevIndex = index;
        }
         /* Tossing out token2 until further notice */
         token2 = input.substr(input.find(delimiter), input.find(' '));
         /* Erases everything up until next index */
         input.erase(0, token.length() + token2.length());
        }
    } else {
        /* If there aren't any slashes, parses like coordinates */
        return coordinateScanner(input);
    }
    return toReturn;
}

obj::vertex obj::parseVertex(string input)
{
    vector<float> coords = coordinateScanner(input);
    Vertex newVertex(Point(coords.at(0), coords.at(1), coords.at(2)));
    return newVertex;
}

vector<float> obj::coordinateScanner(string line)
{
    vector<float> toReturn;
    float vertexArr[3];
    sscanf(line.c_str(), "%*s %f %f %f", &vertexArr[0], &vertexArr[1], &vertexArr[2]);
    toReturn.push_back(vertexArr[0]);
    toReturn.push_back(vertexArr[1]);
    toReturn.push_back(vertexArr[2]);
    return toReturn;
}

std::vector<float> obj::getMinCoords()
{
    return minCoords;
}

std::vector<float> obj::getMaxCoords()
{
    return maxCoords;
}

void obj::checkMin(Vertex v)
{
    float x,y,z;
    x = v.point().hx();
    y = v.point().hy();
    z = v.point().hz();
    if (x < minCoords.at(0))
        minCoords[0] = x;
    if (y < minCoords.at(1))
        minCoords[1] = y;
    if (z < minCoords.at(2))
        minCoords[2] = z;
}

void obj::checkMax(Vertex v)
{
    float x,y,z;
    x = v.point().hx();
    y = v.point().hy();
    z = v.point().hz();
    if (x > maxCoords.at(0))
        maxCoords[0] = x;
    if (y > maxCoords.at(1))
        maxCoords[1] = y;
    if (z > maxCoords.at(2))
        maxCoords[2] = z;
}

vector<float> obj::findCenter()
{
    center[0] = (minCoords.at(0) + maxCoords.at(0))/2;
    center[1] = (minCoords.at(1) + maxCoords.at(1))/2;
    center[2] = (minCoords.at(2) + maxCoords.at(2))/2;
    return center;
}

float obj::findRadius()
{
    radius = sqrt((maxCoords.at(0) - center.at(0))*(maxCoords.at(0) - center.at(0))
                  +(maxCoords.at(1) - center.at(1))*(maxCoords.at(1) - center.at(1))
                  +(maxCoords.at(2) - center.at(2))*(maxCoords.at(2) - center.at(2)));
    return (radius);
}

