/* Adapted From:
 * http://code.metager.de/source/xref/lib/cgal/4.2/examples/Polyhedron/polyhedron_prog_vertex_normal.cpp */
#ifndef MYITEMS
#define MYITEMS
#include<CGAL/HalfedgeDS_default.h>
#include<CGAL/Simple_cartesian.h>
#include<CGAL/Modifier_base.h>
#include<CGAL/Polyhedron_3.h>
#include<CGAL/Polyhedron_incremental_builder_3.h>
// Volume Mesh
#include<CGAL/Mesh_triangulation_3.h>
#include<CGAL/Polyhedron_copy_3.h>
#include<CGAL/Mesh_complex_3_in_triangulation_3.h>
#include<CGAL/Mesh_criteria_3.h>
#include<CGAL/Mesh_polyhedron_3.h>
#include<CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include<CGAL/make_mesh_3.h>
#include<CGAL/refine_mesh_3.h>
#include <CGAL/Mesh_3/Robust_intersection_traits_3.h>
#include <CGAL/Mesh_domain_with_polyline_features_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

/***** Normals *****/
struct Facet_normal {
  template <class Facet>
  void operator()( Facet& f) {
      typename Facet::Halfedge_handle h = f.halfedge();
      typename Facet::Normal_3 normal = CGAL::normal(h->next()->vertex()->point(),
                                                     h->vertex()->point(),
                                                     h->prev()->vertex()->point());
      f.normal() = normal / std::sqrt( normal * normal);
  }
};

struct Vertex_normal {
  template <class Vertex>
  void operator()( Vertex& v) {
      typename Vertex::Normal_3 normal = CGAL::NULL_VECTOR;
      typedef typename Vertex::Halfedge_around_vertex_const_circulator Circ;
      Circ c = v.vertex_begin();
      Circ d = c;
      CGAL_For_all( c, d) {
          if ( ! c->is_border())
              normal = normal + c->facet()->normal();
      }
      v.normal() = normal / std::sqrt( normal * normal);
  }
};

/***** My Vertex *****/
template <class Refs, class T, class P, class Norm>
class My_vertex : public CGAL::HalfedgeDS_vertex_base<Refs, T, P> {
  Norm  norm;
public:
  My_vertex() {}
  My_vertex( const P& pt) : CGAL::HalfedgeDS_vertex_base<Refs, T, P>(pt) {}
  typedef Norm Normal_3;
  Normal_3&       normal()       { return norm; }
  const Normal_3& normal() const { return norm; }
};

/***** My Facet *****/
template <class Refs, class T, class Norm>
class My_facet : public CGAL::HalfedgeDS_face_base<Refs, T> {
  Norm  norm;
public:
  typedef Norm Normal_3;
  Normal_3&       normal()       { return norm; }
  const Normal_3& normal() const { return norm; }
};

/***** My Items *****/
struct My_items : public CGAL::Polyhedron_items_3 {
  template <class Refs, class Traits>
  struct Vertex_wrapper {
      typedef typename Traits::Point_3  Point;
      typedef typename Traits::Vector_3 Normal;
      typedef My_vertex<Refs, CGAL::Tag_true, Point, Normal> Vertex;
  };
  template <class Refs, class Traits>
  struct Face_wrapper {
      typedef typename Traits::Vector_3 Normal;
      typedef My_facet<Refs, CGAL::Tag_true, Normal> Face;
  };
};


typedef double Real;
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Mesh_3::Robust_intersection_traits_3<Kernel> IGT;
typedef CGAL::Polyhedron_3<IGT, My_items> Polyhedron;
typedef CGAL::Polyhedron_3<IGT> Polyhedron2;
typedef Polyhedron::HalfedgeDS HalfedgeDS;
typedef CGAL::Point_3<Kernel> Point;
using namespace std;

//Volume Mesh
typedef CGAL::Mesh_polyhedron_3<IGT>::Type Mesh_polyhedron;
typedef CGAL::Polyhedral_mesh_domain_with_features_3<IGT, Polyhedron2> MeshDomain;
typedef CGAL::Mesh_triangulation_3<MeshDomain>::type Tr;
typedef CGAL::Mesh_complex_3_in_triangulation_3<Tr,MeshDomain::Corner_index,MeshDomain::Curve_segment_index> C3T3;
typedef CGAL::Mesh_criteria_3<Tr> MeshCriteria;
typedef CGAL::Polyhedron_copy_3<Polyhedron, Mesh_polyhedron> Poly_copy;


template <class HDS>
#endif // MYITEMS

