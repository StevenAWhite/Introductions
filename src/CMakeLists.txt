cmake_minimum_required(VERSION 3.20)
find_package(SWIG REQUIRED COMPONENTS csharp)

cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)
cmake_policy(SET CMP0122 NEW)

include(UseSWIG)
include(CSharpUtilities)

set(SWIG_SOURCE_FILE_EXTENSIONS ".swg")
set(UseSWIG_TARGET_NAME_PREFERENCE STANDARD)

set_property(SOURCE swig/example.swg PROPERTY CPLUSPLUS ON 
                                         UseSWIG_MODULE_VERSION 2  
                                         USE_TARGET_INCLUDE_DIRECTORIES ON
                                         SWIG_MODULE_NAME "SWIG_example" 
                                         INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/cpp"
)


add_library(example SHARED cpp/example.cpp cpp/example.h)


#
#  We are looking at two CSharp language bugs
#  1.  All files in the CMAKE_BINARY_DIR tree are attached as <NONE Target=><Link></LINK><NONE Target>
#  2.  Links do not respect SOURCE_GROUP leading to flat source layouts
#
#  Note that the Choice of Link is likely a bad idea as you can not link to sources which are in the same file tree
#  As the vsproj file.  In this example Linked files appear flat and in the solution explorer, but are not compiled 
#  Resulting in a buid failure

swig_add_library(example_swig 
      TYPE SHARED 
      LANGUAGE csharp 
      SOURCES swig/example.swg
      OUTPUT_DIR "${CMAKE_BINARY_DIR}/bindings/csharp/"
      OUTFILE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated"
)
target_include_directories(example_swig PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cpp")
target_link_libraries(example_swig PUBLIC example)
 set_target_properties(example_swig PROPERTIES
   POSITION_INDEPENDENT_CODE ON
)  

if(WIN32)
  enable_language(CSharp)
  message(STATUS "swig_generated_csharp=${swig_generated_csharp}")
  add_executable(example_cs_outside_binary_tree ${swig_generated_csharp} csharp/CSharpSwigExample.cs)
endif()
