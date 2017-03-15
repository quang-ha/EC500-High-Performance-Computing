// ESW 2015
// The function getFunction returns a function pointer based on an input enum defined
// in getFunction.h.

#include <math.h>

#include "getFunction.h"


// Corresponds to FunctionName::XSQUARE
double xsquare(double x)
{
   return x*x;
}

// Corresponds to FunctionName::XLOGABSX
double xlogabsx(double x)
{
   if (x == 0.0)
      return 0;
   else
      return x*log(fabs(x));
}

// Correspinds to FunctionName::GAUSSIAN
double gaussian(double x)
{
   return exp(-x*x);
}

// Corresponds to FunctionName::SINXDIVX
double sinxdivx(double x)
{
   // Worry about nunerical stability, use the series!
   if (fabs(x) < 1e-6)
   {
      double y = x*x;
      // Horner's method for evaluating series.
      return 1-y/(2.0*3.0)*(1-y/(4.0*5.0)*(1-y/(6.0*7.0)*(1-y/(8.0*9.0))));
   }
   else
   {
      return sin(x)/x;
   }
}

// Corresponds to FunctionName::INV1PXSQUARE
double inv1pxsquare(double x)
{
   return 1/(1+x*x);
}


// Return the appropriate function pointer.
DblFunction getFunction(FunctionName fnType)
{
   switch (fnType)
   {
      case XSQUARE:
         return &xsquare;
         break;
      case XLOGABSX:
         return &xlogabsx;
         break;
      case GAUSSIAN:
         return &gaussian;
         break;
      case SINXDIVX:
         return &sinxdivx;
         break;
      case INV1PXSQUARE:
         return &inv1pxsquare;
         break;
   }
   return 0;
}

