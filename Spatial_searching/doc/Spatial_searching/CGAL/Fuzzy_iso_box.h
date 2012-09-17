namespace CGAL {

/*!
\ingroup RangeQueryItemClasses 

The class `Fuzzy_iso_box` implements fuzzy \f$ d\f$-dimensional iso boxes. A 
fuzzy iso box with fuzziness value \f$ \epsilon\f$ has as outer 
approximation a box dilated, and as inner approximation a box eroded 
by a \f$ d\f$-dim square with side length \f$ \epsilon\f$. 

### Parameters ###

Expects for the template argument a model of the concept 
`SearchTraits`, for example `CGAL::Search_traits_2<CGAL::Simple_cartesian<double> >`. 

\models ::FuzzyQueryItem 

\sa `FuzzyQueryItem` 

*/
template< typename Traits >
class Fuzzy_iso_box {
public:

/// \name Types 
/// @{

/*! 
Point type. 
*/ 
Traits::Point_d Point_d; 

/*! 
Number type. 
*/ 
Traits::FT FT; 

/// @} 

/// \name Creation 
/// @{

/*! 
Constructs a fuzzy iso box 
specified by the minimal iso box containing `p` and `q` and fuzziness value `epsilon`. 
\pre `p` must be lexicographically smaller than `q`. 
*/ 
Fuzzy_iso_box(Point_d p, Point_d q, FT epsilon=FT(0),Traits t=Traits()); 

/*! 
Constructs a fuzzy iso box specified by the minimal iso box containing `p` and `q` and fuzziness value `epsilon`. 

\attention Only available in case `Traits` is
`Search_traits_adapter<Key,PointPropertyMap,BaseTraits>`.

\pre `p` must be lexicographically smaller than `q`. 
*/ 
Fuzzy_iso_box(Traits::Base::Point_d p, Traits::Base::Point_d q, FT epsilon=FT(0), Traits t=Traits()); 

/// @} 

/// \name Operations 
/// @{

/*! 
test whether `b` contains `p`. 
*/ 
bool contains(Point_d p) const; 

/*! 
test whether the inner box intersects the rectangle 
associated with a node of a tree. 
*/ 
bool inner_range_intersects(const Kd_tree_rectangle<FT>& rectangle) const; 

/*! 
test whether the outer box encloses the rectangle associated with a node of a tree. 
*/ 
bool outer_range_contains(const Kd_tree_rectangle<FT>& rectangle) const; 

/// @}

}; /* end Fuzzy_iso_box */
} /* end namespace CGAL */
