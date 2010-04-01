# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( Arithmetic_kernel_test )

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)


if ( COMMAND cmake_policy )
  cmake_policy( SET CMP0003 NEW )  
endif()
 
find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )
  include( CGAL_VersionUtils )
  find_package( MPFI )
  IS_VERSION_LESS("${CGAL_GMP_VERSION}" "4.2.0" _IS_GMP_VERSION_TO_LOW)
  
  include_directories(../../include)
  include_directories(include)

  include( CGAL_CreateSingleSourceCGALProgram )

  create_single_source_cgal_program( "CORE_arithmetic_kernel.cpp" )
  create_single_source_cgal_program( "LEDA_arithmetic_kernel.cpp" )

  if( MPFI_FOUND )
    # for the testsuite, the version of MPFI shipped with RS is used; this
    # version needs GMP>=4.2, so we require this dependency only here and
    # not in FindMPFI.cmake
    if( _IS_GMP_VERSION_TO_LOW )
      message( STATUS
        "MPFI tests need GMP>=4.2, some of the tests will not be compiled" )
    else( _IS_GMP_VERSION_TO_LOW )
      include( ${MPFI_USE_FILE} )
        create_single_source_cgal_program( "GMP_arithmetic_kernel.cpp" )      
    endif( _IS_GMP_VERSION_TO_LOW )
  else( MPFI_FOUND )
    message( STATUS
      "MPFI is not present, some of the tests will not be compiled." )
  endif( MPFI_FOUND )

  create_single_source_cgal_program( "Arithmetic_kernel.cpp" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()
