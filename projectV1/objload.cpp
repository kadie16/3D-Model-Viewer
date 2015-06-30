#include "objload.h"
#include <QtWidgets>

objLoad::objLoad()
{
  /*  std::list<double> vertices; // empty list of ints
    std::list<double> facets;  // four ints with value 100
    openFileNameLabel = new QLabel;
    openFileNameLabel->setFrameStyle(frameStyle);
    QPushButton *openFileNameButton =
            new QPushButton(tr("QFileDialog::get&OpenFileName()")); */
}

void objLoad::setOpenFileName()
{

    int testa=5;
    testa;
   /* const QFileDialog::Options options = QFlag(fileDialogOptionsWidget->value());
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("QFileDialog::getOpenFileName()"),
                                openFileNameLabel->text(),
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
        openFileNameLabel->setText(fileName); */
}

// reads the first integer from a string in the form
// "334/455/234" by stripping forward slashes and
// scanning the result
int get_first_integer( const char *v ){
 int ival;
 std::string s( v );
 std::replace( s.begin(), s.end(), '/', ' ' );
 sscanf( s.c_str(), "%d", &ival );
 return ival;
}

void load_obj( const char *filename, std::vector<double> &coords, std::vector<int> &tris ){
 double x, y, z;
 char line[1024], v0[1024], v1[1024], v2[1024];

 // open the file, return if open fails
 FILE *fp = fopen(filename, "r" );
 if( !fp ) return;

 // read lines from the file, if the first character of the
 // line is 'v', we are reading a vertex, otherwise, if the
 // first character is a 'f' we are reading a facet
 while( fgets( line, 1024, fp ) ){
  if( line[0] == 'v' ){
   sscanf( line, "%*s%lf%lf%lf", &x, &y, &z );
   coords.push_back( x );
   coords.push_back( y );
   coords.push_back( z );
  } else if( line[0] == 'f' ){
   sscanf( line, "%*s%s%s%s", v0, v1, v2 );
   tris.push_back( get_first_integer( v0 )-1 );
   tris.push_back( get_first_integer( v1 )-1 );
   tris.push_back( get_first_integer( v2 )-1 );
  }
 }
 fclose(fp);
}
