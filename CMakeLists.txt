project(SWIG_Demonstration LANGUAGES CXX CSharp)
cmake_minimum_required(VERSION 3.0)

add_library(example SHARED example.cpp)

find_package(SWIG REQUIRED COMPONENTS csharp)

cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)
cmake_policy(SET CMP0122 NEW)

include(UseSWIG)
include(CSharpUtilities)

set(SWIG_SOURCE_FILE_EXTENSIONS ".swg")
set(UseSWIG_TARGET_NAME_PREFERENCE STANDARD)

set_property(SOURCE example.swg PROPERTY CPLUSPLUS ON 
                                         UseSWIG_MODULE_VERSION 2  
                                         USE_TARGET_INCLUDE_DIRECTORIES ON
                                         SWIG_MODULE_NAME "SWIG_example" 
)
set_property(SOURCE ${_file} PROPERTY COMPILE_OPTIONS )

swig_add_library(example_swig 
      TYPE SHARED 
      LANGUAGE csharp 
      SOURCES example.swg
      OUTPUT_DIR "${PROJECT_BINARY_DIR}/csharp"
      OUTFILE_DIR "${PROJECT_BINARY_DIR}/csharp"
)
target_include_directories(example_swig PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(example_swig PUBLIC example)
 set_target_properties(example_swig PROPERTIES
   POSITION_INDEPENDENT_CODE ON
)  
 
