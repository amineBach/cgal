// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       :
// release_date  :
//
// file          : Triangulation/include/CGAL/Triangulation_euclidean_traits_yz_3
// source        : RCSfile$
// revision      : $Revision$
// revision_date : $Date$
//
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec  < Mariette Yvinec@sophia.inria.fr>
//
// ============================================================================

#ifndef CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_YZ_3_H
#define CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_YZ_3_H

#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Distance_2.h>

#include <CGAL/Point_3.h>
#include <CGAL/Segment_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/predicates_on_ftC2.h>

CGAL_BEGIN_NAMESPACE

template < class R >
class Triangulation_euclidean_traits_yz_3 {
public:
    typedef Triangulation_euclidean_traits_yz_3<R> Traits;
    typedef R Rep;
    typedef Point_3<R>  Point;
    typedef Segment_3<R> Segment;
    typedef Triangle_3<R> Triangle;
    typedef Line_3<R>   Line;
    typedef Ray_3<R>    Ray;
    typedef Direction_3<R> Direction;
    
   
    
      typename Rep::FT x(const Point &p) const { return p.y(); }
      typename Rep::FT y(const Point &p) const { return p.z(); }
    
    Comparison_result compare_x(const Point &p, const Point &q) const
      {
        return CGAL::compare(x(p), x(q));
      }
    Comparison_result compare_y(const Point &p, const Point &q) const
      {
        return CGAL::compare(y(p), y(q));
      }
    bool compare(const Point &p, const Point &q) const
      {
        return (x(p)==x(q)) &&  (y(p)==y(q));
      }
    
    Orientation orientation(const Point &p,
                                 const Point &q,
                                 const Point &r) const
      {
        return orientationC2(x(p), y(p), x(q), y(q), x(r), y(r));
      }
    
    Orientation extremal(const Point &p,
                              const Point &q,
                              const Point &r) const
      {
        if (compare(p,q)) return COLLINEAR;
        if (compare(p,r)) return COLLINEAR;
        if (compare(r,q)) return COLLINEAR;
    
        return orientationC2(x(p), y(p), x(q), y(q), x(r), y(r));
      }
    
    Oriented_side side_of_oriented_circle(const Point &p,
                                               const Point &q,
                                               const Point &r,
                                               const Point &s) const
      {
        if (compare(p,s)) return ON_ORIENTED_BOUNDARY;
        if (compare(q,s)) return ON_ORIENTED_BOUNDARY;
        if (compare(r,s)) return ON_ORIENTED_BOUNDARY;
    
        return side_of_oriented_circleC2(x(p), y(p),
                                              x(q), y(q),
                                              x(r), y(r),
                                              x(s), y(s));
      }
    

        
    class Distance : public Distance_2<Traits> {
    public:
        Distance(const Point& p0,
                 const Traits* traits = NULL)
            : Distance_2<Traits>(p0, traits) { }
    
    
        Distance(const Point& p0,
                 const Point& p1,
                 const Traits* traits = NULL)
            : Distance_2<Traits>(p0,p1,traits) { }
    
        Distance(const Point& p0,
                 const Point& p1,
                 const Point& p2,
                 const Traits* traits = NULL)
            : Distance_2<Traits>(p0,p1,p2,traits) { }
    
        Comparison_result
        compare() const
        {
          Point p0 = get_point(0);
          Point p1 = get_point(1);
          Point p2 = get_point(2);
          return cmp_dist_to_pointC2(x(p0),y(p0),x(p1),y(p1),x(p2),y(p2));
        }
    };
    
};


CGAL_END_NAMESPACE


#endif // CGAL_TRIANGULATION_EUCLIDEAN_TRAITS_YZ_3_H
