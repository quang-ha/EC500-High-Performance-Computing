#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::ios;
using std::cos;
using std::fabs;

int getLegendreCoeff(double* a, int n);

int getLegendreZero(double* zero, double* a, int n);

int main(int argc, char** argv)
{

  // Fix the output format.
  cout.setf(ios::fixed,ios::floatfield);
  cout.precision(20);

  // Order of Legendre polynomial
  int order = 0;

  // Space to hold coefficients
  double* coeffs = 0;

  // Describe the problem and prompt the user:
  cout << "What order Legendre polynomial? ";
  cin >> order;

  if (order < 0) {
    cout << "Error! The Legendre polynomial needs to be of positive integer order.\n";
    return -1;
  }

  // Allocate the coefficients
  coeffs = new double[order+1];

  // Get the coefficients
  if (getLegendreCoeff(coeffs, order) == -1) {
    cout << "Error! The coefficient array wasn't allocated.\n";
    return -1;
  }

  // Print
  std::cout << "Coefficients\n"; 
  for (int i = order; i > 0; i--) {
    std::cout << coeffs[i] << " x^" << i << " + ";
  }
  std::cout << coeffs[0] << " x^0\n";

  // Compute the zeros
  double* zeros = new double[order];
  if (getLegendreZero(zeros, coeffs, order) == -1) {
    cout << "Error! The zeros array wasn't allocated.\n";
    delete[] coeffs;
    return -1;
  }

  // Print
  std::cout << "Zeros\n";
  for (int i = 0; i < order; i++) {
    std::cout << zeros[i] << " ";
  }
  std::cout << "\n";

  // Clean up
  delete[] coeffs;

}

// This function's wasteful because every time you run it
// you have to re-compute the entire recursive stack.
// But whatever.
int getLegendreCoeff(double* a, int n)
{
  if (a == 0) { return -1; } // error out if not allocated
  
  // The startup cases
  if (n == 0) { a[0] = 1.0; return 0; }
  if (n == 1) { a[0] = 0.0; a[1] = 1.0; return 0; }

  // Allocate space for each set of coefficients
  double** coeffs;

  // Allocate things.
  coeffs = new double*[n+1];

  // Fill out the startup cases
  coeffs[0] = new double[1];
  coeffs[0][0] = 1.0;
  coeffs[1] = new double[2];
  coeffs[1][0] = 0.0;
  coeffs[1][1] = 1.0;

  // And go go go
  for (int m = 2; m <= n; m++)
  {
    coeffs[m] = new double[m+1];

    // Start filling up the coefficients. Handle the 0th coefficient
    // because of the "i-1"
    coeffs[m][0] = -((double)m - 1.0)/m * coeffs[m-2][0];
    for (int i = 1; i <= m; i++)
    {
      coeffs[m][i] = (1.0/m)*( (2.0*m-1.0)*coeffs[m-1][i-1] - (m - 1.0)*coeffs[m-2][i] );
    }
    
  }

  // Copy the last row in
  for (int i = 0; i <= n; i++)
  {
    a[i] = coeffs[n][i];
  }

  // Clean up
  for (int i = 0; i <= n; i++)
  {
    delete[] coeffs[i];
  }
  delete[] coeffs;

  return 0;

}

// evaluate a polynomial of order 'n'
double evalPolynomial(double x, double* a, int n)
{
  if (n == 0) { return a[0]; }
  double sum = a[0];
  double x_pow = x;
  for (int i = 1; i <= n; i++)
  {
    sum += a[i]*x_pow;
    x_pow *= x;
  }

  return sum;
}

// evaluate the derivative of a polynomial of order 'n'
double evalPolyDeriv(double x, double* a, int n)
{
  if (n == 0) { return 0; }
  if (n == 1) { return a[1]; }
  double sum = a[1];
  double x_pow = x;
  for (int i = 2; i <= n; i++)
  {
    sum += a[i]*i*x_pow;
    x_pow *= x;
  }

  return sum;
}

int getLegendreZero(double* zero, double* a, int n)
{
  if (zero == 0) { return -1; } // error out if not allocated
  if (a == 0) { return -1; } // error out if not allocated

  for (int i = 1; i <= n; i++)
  {
    std::cout << "Zero " << i << "\n";
    // Get the approximate zero
    double approx_zero = (1.0 - 1.0/(8.0*n*n) + 1.0/(8.0*n*n*n))*cos(M_PI*(4.0*i-1.0)/(4*n+2));
    
    // Here's a place to store a new guess.
    double new_zero = approx_zero;
    
    // check that the approximate zero isn't too small and that we haven't hit tolerance
    do
    {
      std::cout << new_zero << "\n";
      approx_zero = new_zero;
      new_zero = approx_zero - evalPolynomial(approx_zero,a,n)/evalPolyDeriv(approx_zero,a,n);
    } while (new_zero > 1e-8 && fabs((approx_zero - new_zero)/approx_zero) > 1e-8);

    // converged
    zero[n-i] = new_zero;
  }

  return 0;

}

