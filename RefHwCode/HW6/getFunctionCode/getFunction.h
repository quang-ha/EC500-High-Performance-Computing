// ESW 2015
// An interface header to return function pointers to functions defined in
// in getFunction.cpp.

#ifndef GETFUNCTION
#define GETFUNCTION

// An enum of functions defined in getFunction.cpp
enum FunctionName
{
  XSQUARE, // x^2
  XLOGABSX,    // xlog|x|
  GAUSSIAN, // exp(-x^2)
  SINXDIVX,  // sin(x)/x
  INV1PXSQUARE // 1/(1+x^2)
};

// A typedef of a function pointer.
typedef double (*DblFunction)(double);

// A function which returns a function pointer depending
// on the enum value passed to it.
DblFunction getFunction(FunctionName fnType);

#endif // GETFUNCTION

