#include <iostream>
#include <iomanip>

#include "getFunction.h"

int main(int argc, char** argv)
{
   // Declare a function pointer.
   DblFunction fcn;

   // Get the squared function.
   fcn = getFunction(XSQUARE);

   // Format output.
   std::cout << std::setprecision(16) << std::scientific;   

   // Print something!
   std::cout << "3^2 equals " << (*fcn)(3.0) << std::endl;

   // Get a different function!
   fcn = getFunction(SINXDIVX);

   // Print something else!
   std::cout << "sin(3)/3 equals " << (*fcn)(3.0) << std::endl;

   return 0;

}


