 
namespace CGAL {

/*!
\ingroup PkgAlphaShape2

The class `Alpha_shape_2` represents the family of 
\f$ \alpha\f$-shapes of points in a plane for <I>all</I> positive 
\f$ \alpha\f$. It maintains the underlying triangulation `Dt` which 
represents connectivity and order among its faces. Each 
\f$ k\f$-dimensional face of the `Dt` is associated with 
an interval that specifies for which values of \f$ \alpha\f$ the face 
belongs to the \f$ \alpha\f$-shape. There are links between the intervals 
and the \f$ k\f$-dimensional faces of the triangulation. 

Note that this class is at the same time used for <I>basic</I> and 
for <I>weighted</I> Alpha Shapes. 

### Parameters ###

The template parameter `Dt` has to be either `Delaunay_triangulation_2` or `Regular_triangulation_2`. 
Note that `DT::Geom_traits`, `DT::Vertex` and `DT::Face` must model the concepts `AlphaShapeTraits_2`, 
`AlphaShapeVertex_2` and `AlphaShapeFace_2` respectively. 

The template parameter `ExactAlphaComparisonTag` is a tag that, when set to 
`CGAL::Tag_true`, triggers exact comparisons between alpha values. This is useful 
when the underlying triangulation is instantiated with an exact predicates inexact constructions 
kernel. By default the `ExactAlphaComparisonTag` is set to `CGAL::Tag_false` as it induces a small 
overhead. Note that since such a strategy does not make sense if used together with a traits class with exact constructions, 
the tag `ExactAlphaComparisonTag` is not taken into account if `Dt::Geom_traits::FT` is not a floating point number type. 

### Inherits From ###

Inherits from `Dt`.

This class is the underlying triangulation class. 

The modifying functions `insert` and `remove` will overwrite 
the inherited functions. At the moment, only the static version is implemented. 

### I/O ###

The I/O operators are defined for `std::iostream`. The format for the iostream 
is an internal format. 

### Implementation ###

The set of intervals associated with the 
\f$ k\f$-dimensional faces of the underlying triangulation are 
stored in `multimaps`. 

The cross links between the intervals and the \f$ k\f$-dimensional faces of the 
triangulation are realized using methods in the \f$ k\f$-dimensional faces 
themselves. 

`A.alpha_find` uses linear search, while 
`A.alpha_lower_bound` and `A.alpha_upper_bound` 
use binary search. 
`A.number_of_solid_components` performs a graph traversal and takes time 
linear in the number of faces of the underlying triangulation. 
`A.find_optimal_alpha` uses binary search and takes time 
\f$ O(n \log n)\f$, where \f$ n\f$ is the number of points. 

*/
template< typename Dt, typename ExactAlphaComparisonTag >
class Alpha_shape_2 : public Dt {
public:

/// \name Types 
/// @{

/*! 
the alpha shape traits type. 
it has to derive from a triangulation traits class. For example `Dt::Point` is a point class.
*/ 
typedef Hidden_type Gt; 

/*! 
the number type for computation. 
*/ 
typedef Gt::FT FT; 

/*! 
The size type. 
*/ 
typedef Hidden_type size_type; 

/*! 
A bidirectional and non-mutable iterator that allow to traverse 
the increasing sequence of different \f$ \alpha\f$-values. 
\pre Its `value_type` is `FT`. 
*/ 
typedef Hidden_type Alpha_iterator; 

/*! 
A bidirectional and non-mutable iterator that allow to traverse 
the vertices which belongs to the \f$ \alpha\f$-shape for the current \f$ \alpha\f$. 
\pre Its `value_type` is `Dt::Vertex_handle`. 
*/ 
typedef Hidden_type Alpha_shape_vertices_iterator; 

/*! 
A bidirectional and non-mutable iterator that allow to traverse 
the edges which belongs to the \f$ \alpha\f$-shape for the current \f$ \alpha\f$. 
\pre Its `value_type` is `Dt::Edge`. 
*/ 
typedef Hidden_type Alpha_shape_edges_iterator; 

/*! 
Distinguishes the different cases for classifying a \f$ k\f$-dimensional face 
of the underlying triangulation of the \f$ \alpha\f$-shape. 

`EXTERIOR` if the face does not belong to the \f$ \alpha\f$-complex. 

`SINGULAR` if the face belongs to the boundary of the \f$ \alpha\f$-shape, 
but is not incident to any 2-dimensional face of the \f$ \alpha\f$-complex 

`REGULAR` if the face belongs to the boundary of the \f$ \alpha\f$-shape 
and is incident to a 2-dimensional face of the \f$ \alpha\f$-complex 

`INTERIOR` if the face belongs to the \f$ \alpha\f$-complex, but does 
not belong to the boundary of the \f$ \alpha\f$-shape. 

*/ 
enum Classification_type {EXTERIOR, SINGULAR, REGULAR, INTERIOR}; 

/*! 
In general, an alpha shape can be disconnected and contain many singular edges 
or vertices. Its regularized version is formed by the set of regular edges 
and their vertices. 
*/ 
enum Mode {GENERAL, REGULARIZED}; 

/// @} 

/// \name Creation 
/// @{

/*! 
Introduces an empty \f$ \alpha\f$-shape `A` for a positive \f$ \alpha\f$-value 
`alpha`. 
\pre `alpha` \f$ \geq~0\f$. 
*/ 
Alpha_shape_2(FT alpha = 0, 
Mode m = GENERAL); 

/*! 
Builds an alpha shape `A` of mode `m` from the triangulation `dt` 
for a positive \f$ \alpha\f$-value `alpha`. 
\attention This operation destroys the triangulation. 
\pre `alpha` \f$ \geq~0\f$. 
*/ 
Alpha_shape_2( 
Dt& dt, 
FT alpha = 0, 
Mode m = GENERAL); 

/*! 
Initializes the family of alpha-shapes with the points in the range 
\f$ \left[\right.\f$`first`, `last`\f$ \left.\right)\f$ and 
introduces an \f$ \alpha\f$-shape `A` for a positive \f$ \alpha\f$-value 
`alpha`. 
\pre The `value_type` of `first` and `last` is `Point`. 
`alpha` \f$ \geq0\f$. 
*/ 
template < class InputIterator > 
Alpha_shape_2( 
InputIterator first, 
InputIterator last, 
const FT& alpha = 0, 
Mode m = GENERAL); 

/// @} 

/// \name Operations 
/// @{

/*! 
Initialize the family of alpha-shapes with the points in the range 
\f$ \left[\right.\f$`first`, `last`\f$ \left.\right)\f$. Returns the number of 
inserted points. 

If the function is applied to an non-empty family of alpha-shape, it is cleared 
before initialization. 
\pre The `value_type` of `first` and `last` is `Point`. 
*/ 
template < class InputIterator > 
std::ptrdiff_t make_alpha_shape( 
InputIterator first, 
InputIterator last); 

/*! 
Clears the structure. 
*/ 
void 
clear(); 

/*! 
Sets the \f$ \alpha\f$-value to `alpha`. 
Returns the previous \f$ \alpha\f$-value. 
\pre `alpha` \f$ \geq0\f$. 
*/ 
FT 
set_alpha(const FT& alpha); 

/*! 
Returns the current \f$ \alpha\f$-value. 
*/ 
const FT& 
get_alpha(void) const; 

/*! 
Returns the `n`-th \f$\alpha\f$-value, sorted in an increasing order. 
\pre `n` \f$ <\f$ number of alphas. 
*/ 
const FT& get_nth_alpha(size_type n) const; 

/*! 
Returns the number of different alpha-values. 
*/ 
size_type number_of_alphas() const; 

/*! 
Sets `A` to its general or regularized version. 
Returns the previous mode. 
*/ 
Mode 
set_mode(Mode m = GENERAL ); 

/*! 
Returns whether `A` is general or regularized. 
*/ 
Mode 
get_mode(void) const; 

/*! 
Starts at 
an arbitrary finite vertex which belongs to the \f$ \alpha\f$-shape for the current \f$ \alpha\f$. 
*/ 
Alpha_shape_vertices_iterator alpha_shape_vertices_begin(); 

/*! 
Past-the-end iterator. 
*/ 
Alpha_shape_vertices_iterator alpha_shape_vertices_end(); 

/*! 
Starts at 
an arbitrary finite edge which belongs to the \f$ \alpha\f$-shape for the current 
\f$ \alpha\f$. In regularized mode, edges are represented as a pair (f,i), where f is 
an interior face of the \f$ \alpha\f$-shape. 
*/ 
Alpha_shape_edges_iterator alpha_shape_edges_begin(); 

/*! 
Past-the-end iterator. 
*/ 
Alpha_shape_edges_iterator alpha_shape_edges_end(); 

/// @} 

/// \name Predicates 
/// @{

/*! 
Locates a point `p` in the underlying triangulation and Classifies the 
associated k-face with respect to `A`. 
*/ 
Classification_type 
classify(const Point& p, 
const FT& alpha = get_alpha()) const; 

/*! 
Classifies the face `f` of the underlying triangulation with respect to `A`. 
*/ 
Classification_type 
classify(Face_handle f, const FT& alpha = get_alpha()) const; 

/*! 
Classifies the edge `e` of the underlying triangulation with respect to `A`. 
*/ 
Classification_type 
classify(Edge e, const FT& alpha = get_alpha()) const; 

/*! 
Classifies the edge of the face `f` opposite to the vertex with index 
`i` 
of the underlying triangulation with respect to `A`. 
*/ 
Classification_type 
classify(Face_handle f, int i, const FT& alpha = get_alpha()) const; 

/*! 
Classifies the vertex `v` of the underlying triangulation with respect to `A`. 
*/ 
Classification_type 
classify(Vertex_handle v, const FT& alpha = get_alpha()) const; 

/// @} 

/// \name Traversal of the alpha-Values 
/// @{

/*! 
Returns an iterator that allows to traverse the 
sorted sequence of \f$ \alpha\f$-values of the family of alpha shapes. 
*/ 
Alpha_iterator alpha_begin() const; 

/*! 
Returns the corresponding past-the-end iterator. 
*/ 
Alpha_iterator alpha_end() const; 

/*! 
Returns an iterator pointing to an element with \f$ \alpha\f$-value 
`alpha`, or the corresponding past-the-end iterator if such 
an element is not found. 
*/ 
Alpha_iterator alpha_find(const FT& alpha) const; 

/*! 
Returns an iterator pointing to the first element with 
\f$ \alpha\f$-value not less than `alpha`. 
*/ 
Alpha_iterator alpha_lower_bound(const FT& alpha) const; 

/*! 
Returns an iterator pointing to the first element with \f$ \alpha\f$-value 
greater than `alpha`. 
*/ 
Alpha_iterator alpha_upper_bound(const FT& alpha) const; 

/// @} 

/// \name Operations 
/// @{

/*! 
Returns the number of solid components of `A`, that is, the number of 
components of its 
regularized version. 
*/ 
size_type number_of_solid_components(const FT& alpha = get_alpha()) const; 

/*! 
Returns an iterator pointing to the first element with \f$ \alpha\f$-value 
such that `A` satisfies the following two properties: 

`nb_components` equals the number of solid components and 

all data points are either on the boundary or in the interior of the regularized version of `A`. 

If no such value is found, the iterator points to the first element with 
\f$ \alpha\f$-value such that `A` satisfies the second property. 
*/ 
Alpha_iterator find_optimal_alpha(size_type nb_components) const; 

/*! 
Inserts the alpha shape `A` for the current \f$ \alpha\f$-value into the stream `os`. 

\ref CGAL/IO/io.h must be included.

\pre The insert operator must be defined for `Point`. 
\relates Alpha_shape_2 
*/ 
  ostream& operator<<(std::ostream& os, 
const Alpha_shape_2<Dt>& A); 

/// @}

}; /* end Alpha_shape_2 */
} /* end namespace CGAL */
