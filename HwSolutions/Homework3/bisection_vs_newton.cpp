#include <iostream>
#include <iomanip> 
#include <cmath>
#include <float.h> // For long doubles. 

using std::cout;
using std::cin;
using std::endl;
using std::ios;

using std::abs;

// This function performs one iteration of Newton's method
// and returns a new guess (x - f(x)/f'(x) -> x_new).
// For now, you need to hard-code the numerical function and
// its derivative. 
long double newton(long double x, long double A, double N);

// This function performs one iteration of bisection
// and updates either "min" or "max" (note how they are both
// passed by reference), and returns the current "midpoint".
// Again, you need to hard-code the numerical function. Bisection
// does not require a derivative. 
long double bisection(long double A, double N, long double & min, long double & max);

int main()
{
  // Declare variables to hold the current guess
  // and relative error. 
  long double x = 0.0, fractional_error = 0.5;
  
  // Declare a variable to hold "A". 
  long double A;

  // Declare a root "N" to find
  double N;

  // Declare a tolerance
  double log10_tol;
  double tol;
  
  // Declare a counter.
  int count; 
  
  // Print the number of digits a long double can hold.
  cout << "Number of digits accuracy in long double " << LDBL_MANT_DIG << endl;
  
  // Fix the output format.
  cout.setf(ios::fixed,ios::floatfield); 
  cout.precision(20);
  
  // Describe the problem and prompt the user:
  cout << " Compute the Nth root by Newton's Method and the bisection method to a tolerance " << tol << "." << endl;
  cout <<"Give a number A: ";
  cin >> A;
  cout << "Give a number N: ";
  cin >> N;
  cout << "Give a log10 tolerance (i.e., tolerance will be 10^{-[number]}): ";
  cin >> log10_tol;
  tol = pow(10.0,-log10_tol);

  // Choose an initial guess for Newton's method: in this case,
  // A/N. Set the output precision as well.
  x = A/N;
  count = 0;
  cout.precision(20);
  do 
  {
    count++;
    x = newton(x, A, N);
    fractional_error = 0.5*abs(pow(x,N)/A-1.0);
    cout << x << "\t" << fractional_error << endl;
  }
  while(fractional_error > tol && count < 100000);

  cout.precision(40);
  cout << "After " << count << " iterations, Newton's method " << endl;
  cout << "gave = "  << x  <<  " vs cmath = "  << pow(A,1.0/N) << endl; 
  cout.precision(20);
  cout << " relative error   = " << (x - pow(A,1.0/N))/(pow(A,1.0/N)) << endl;

  /*   Compare with bisection */
  cout<< " Bisection Method starting with min = 0 and max = A\n";

  long double min, max;
  min = 0.0;
  max = A;
  count = 0;

  do 
  {
    count++;
    x =  bisection( A, N,  min, max);
    fractional_error = 0.5*abs(pow(x,N)/A-1);
    cout.precision(20);
    cout << x   << "\t" <<  fractional_error << endl;
  }
  while(fractional_error > tol);


  cout.precision(40);
  cout << "Bisection's value  in " << count << " iterations " << endl;
  cout << "gave = "  << x  <<  " vs cmath = "  << pow(A, 1.0/N) << endl;
  cout.precision(20);
  cout << " error   = " << x - pow(A, 1.0/N) << endl;


  return  0;
}

// This routine is currently hard coded for the function
// f(x) = x^N-A.
long double newton(long double x, long double A, double N)
{
  return x*(1 - 1.0/N) + A/(N*pow(x,N-1.0));
}

// This routine is currently hard coded for the function
// f(x) - x^2 - A
long double bisection(long double A, double N, long double & min, long double & max)
{
  long double x  = (min + max)/2.0;
  if(pow(x,N)-A < 0.0)
    min = x;
  else
    max = x;

  return x;
}
