#include <iostream>
#include <iomanip> 
#include <cmath>
#include <float.h> // For long doubles. 

using std::cout;
using std::cin;
using std::endl;
using std::ios;

using std::abs;

// With finite precision, we can't really "exactly" find
// the zero. This define sets the tolerance: how small we 
// want the relative error between the true zero and our
// approximate zero to be. 
#define TOL 1.0E-15

// This function performs one iteration of Newton's method
// and returns a new guess (x - f(x)/f'(x) -> x_new).
// For now, you need to hard-code the numerical function and
// its derivative. 
long double newton(long double x, long double A);

// This function performs one iteration of bisection
// and updates either "min" or "max" (note how they are both
// passed by reference), and returns the current "midpoint".
// Again, you need to hard-code the numerical function. Bisection
// does not require a derivative. 
long double bisection(long double A, long double & min, long double & max);

int main()
{
  // Declare variables to hold the current guess
  // and relative error. 
  long double x = 0.0, fractional_error = 0.5;
  
  // Declare a variable to hold "A". 
  long double A;
  
  // Declare a counter.
  int count; 
  
  // Print the number of digits a long double can hold.
  cout << "Number of digits accuracy in long double " << LDBL_MANT_DIG << endl;
  
  // Fix the output format.
  cout.setf(ios::fixed,ios::floatfield); 
  cout.precision(20);
  
  // Describe the problem and prompt the user:
  cout << " Compute the square root by Newton's Method and the bisection method to a tolerance " << TOL << "." << endl;
  cout <<"Give a number A: ";
  cin >> A;

  // Choose an initial guess for Newton's method: in this case,
  // A/2. Set the output precision as well.
  x = A/2;
  count = 0;
  cout.precision(20);
  do 
  {
    count++;
    x = newton(x, A);
    fractional_error = 0.5*abs(x*x/A-1);
    cout << x << "\t" << fractional_error << endl;
  }
  while(fractional_error > TOL && count < 100000);

  cout.precision(40);
  cout << "After " << count << " iterations, Newton's method " << endl;
  cout << "gave = "  << x  <<  " vs cmath = "  << sqrt(A) << endl; 
  cout.precision(20);
  cout << " relative error   = " << (x - sqrt(A))/(sqrt(A)) << endl;

  /*   Compare with bisection */
  cout<< " Bisection Method starting with min = 0 and max = A\n";

  long double min, max;
  min = 0.0;
  max = A;
  count = 0;

  do 
  {
    count++;
    x =  bisection( A,  min, max);
    fractional_error = 0.5*abs(x*x/A-1);
    cout.precision(20);
    cout << x   << "\t" <<  fractional_error << endl;
  }
  while(fractional_error > TOL);


  cout.precision(40);
  cout << "Bisection's value  in " << count << " iterations " << endl;
  cout << "gave = "  << x  <<  " vs cmath = "  << sqrt(A) << endl;
  cout.precision(20);
  cout << " error   = " << x - sqrt(A) << endl;


  return  0;
}

// This routine is currently hard coded for the function
// f(x) = x^2-A.
long double newton(long double x, long double A)
{
  return x*(1 - 1.0/2.0) + A/(2.0*pow(x,1.0));
}

// This routine is currently hard coded for the function
// f(x) - x^2 - A
long double bisection(long double A, long double & min, long double & max)
{
  long double x  = (min + max)/2.0;
  if(x*x-A < 0.0)
    min = x;
  else
    max = x;

  return x;
}
