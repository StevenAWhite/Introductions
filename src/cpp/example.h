#pragma once


#if defined(_WIN32)
#ifdef example_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else 
#define DLL_EXPORT
#endif


#include <string>

namespace example {
  DLL_EXPORT  std::string print_hello_world();
  DLL_EXPORT  int roll_dice();
}
