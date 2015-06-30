#ifndef OBJLOAD_H
#define OBJLOAD_H
#include <QWidget>
#include <QLabel>
#include <iostream>
#include <list>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
//include<CGAL/Simple_cartesian.h>
//#include<CGAL/Polyhedron_incremental_builder_3.h>
//#include<CGAL/Polyhedron_3.h>
//#include<CGAL/IO/Polyhedron_iostream.h>

//typedef CGAL::Simple_cartesian<double>     Kernel;
//typedef CGAL::Polyhedron_3<Kernel>         Polyhedron;
//typedef Polyhedron::HalfedgeDS             HalfedgeDS;

class objLoad
{
public:
    objLoad();
    void load_obj( const char *filename, std::vector<double> &coords, std::vector<int> &tris );
    int get_first_integer( const char *v );

private slots:
    void setOpenFileName();

private:
    QLabel *openFileNameLabel;

};

#endif // OBJLOAD_H
