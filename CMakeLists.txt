project(SWIG_Demonstration LANGUAGES CXX )
cmake_minimum_required(VERSION 3.20)

#
#  The src directory CMAKE is going to generate SWIG Bindings and place them in this directory
#  We want a later project to use this generated code to write unit test or POC code with
#  We GLOB_RECURSE here for scope
# 
# Due to the CSHarp generated marking all of these files as <NONE> instead of <COMPILE> files neither project will work
# This can be solved by removing the two SWIG binding files and readding them in editor or manually changing the 
# vcproj.  For the outside tree only NONE->COMPILE is needed for the inside target the LINK must be deleted.
# 
#  Behavior Changes Need
#  Treat all *.cs files as a COMPILE unless some SOURCE property is set maybe CSHARP_LINK_ONLY
#  All files which are relative to CMAKE_CURRENT_BINARY_DIR must not be embedded with LINK tags

file(GLOB_RECURSE swig_generated_csharp LIST_DIRECTORIES False CONFIGURE_DEPENDS "${CMAKE_BINARY_DIR}/bindings/csharp/*.cs")

add_subdirectory(src)


#
# This project creates 4 targets
#
# libexample   -- CPP Example Library to use SWIG against
# example_swig -- swig_add_library which generates csharp bindings based on libexample
# example_cs_inside_binary_tree  -- Demonstrates NONE vs COMPILE but also highlights that no SWIG Bindings apear in solution explorer
# example_cs_outside_binary_tree -- Demonstrates NONE vs COMPILE but also highlights that SWIG Binding links do appear

if(WIN32)
  enable_language(CSharp)
  message(STATUS "swig_generated_csharp=${swig_generated_csharp}")
  add_executable(example_cs_inside_binary_tree ${swig_generated_csharp} src/csharp/CSharpSwigExample.cs)
endif()
