%module example

%{
  #include "example.h"
%}

%include "std_string.i"

%nspace example;

%include "../cpp/example.h"