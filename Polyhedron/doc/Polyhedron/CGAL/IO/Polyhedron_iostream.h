namespace CGAL {

/*!
\ingroup PkgPolyhedron
\anchor refPolyhedron_operator_rightshift 

This operator reads a polyhedral surface in Object File Format, OFF, 
with file extension <TT>.off</TT>, which is also understood by 
Geomview \cite cgal:p-gmgv16-96, from the input stream `in` and 
appends it to the polyhedral surface \f$ P\f$. Only the point coordinates 
and facets from the input stream are used to build the polyhedral 
surface. Neither normal vectors nor color attributes are evaluated. If 
the stream `in` does not contain a permissible polyhedral surface 
the `ios::badbit` of the input stream `in` is set and \f$ P\f$ remains 
unchanged. 

For OFF an ASCII and a binary format exist. The stream detects the 
format automatically and can read both. 

\sa \ref ::CGAL::Polyhedron_3<Traits> 
\sa \ref ::CGAL::Polyhedron_incremental_builder_3<HDS> 
\sa operator<<(std::ostream&, CGAL::Polyhedron_3<PolyhedronTraits_3>&)


### Implementation ###

This operator is implemented using the modifier mechanism for 
polyhedral surfaces and the `CGAL::Polyhedron_incremental_builder_3` 
class, which allows the construction in a single, efficient scan pass 
of the input and handles also all the possible flexibility of the 
polyhedral surface. 

*/
template <class PolyhedronTraits_3>
std::istream& operator>>( std::istream& in, CGAL::Polyhedron_3<PolyhedronTraits_3>& P);

/*!
\ingroup PkgPolyhedron

This operator writes the polyhedral surface \f$P\f$ to the output
stream out using the Object File Format, OFF, with file extension
<TT>.off</TT>, which is also understood by GeomView \cite cgal:p-gmgv16-96. The
output is in ASCII format. From the polyhedral surface, only the point
coordinates and facets are written. Neither normal vectors nor color
attributes are used.

For OFF an ASCII and a binary format exist. The format can be selected
with the \cgal modifiers for streams, ::set_ascii_mode and
set_binary_mode respectively. The modifier ::set_pretty_mode can be used
to allow for (a few) structuring comments in the output. Otherwise,
the output would be free of comments. The default for writing is ASCII
without comments.

\sa \ref ::CGAL::Polyhedron_3<Traits> 
\sa \ref ::CGAL::Polyhedron_incremental_builder_3<HDS> 
\sa operator>>(std::istream&, CGAL::Polyhedron_3<PolyhedronTraits_3>&)

*/
template <class PolyhedronTraits_3>
std::ostream& operator<<( std::ostream& out, CGAL::Polyhedron_3<PolyhedronTraits_3>& P);

} /* namespace CGAL */



