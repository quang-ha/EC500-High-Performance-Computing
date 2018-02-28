
#include <cmath>
#include <stdio.h>
#include <chrono>
#include <omp.h>


int main(int argc, char** argv)
{

  // Beginning of interval: x
  double a = -1.0;

  // End of interval: x
  double b = 1.0;

  // Beginning of interval: y
  double c = -1.0;

  // End of interval: y
  double d = 1.0;

  // Number of sub-intervals per dimension
  int N = 5000;

  // Where we accumulate the approximate integral.
  double sum = 0.0;

  // BEGIN TIMING
  std::chrono::time_point<std::chrono::steady_clock> begin_time =
  std::chrono::steady_clock::now();

  // Pre-compute the window width.
  double epsilon_x = (b-a)/((double)N);
  double epsilon_y = (d-c)/((double)N);

  // Perform the integral
  #pragma omp parallel for reduction(+:sum)
  for (int x = 0; x < N; x++)
  {
    for (int y = 0; y < N; y++)
    {
      double xval = a + epsilon_x*((double)x + 0.5);
      double yval = c + epsilon_y*((double)y + 0.5);
      //sum += epsilon_x*epsilon_y*(exp(-(x*x)-(y*y)/8))*cos(3.1415926535*x)*sin(3.1415926535/8.0*x);
      sum += epsilon_x*epsilon_y*(xval*xval + yval*yval + (yval-1.0)*(yval-1.0)*(yval-1.0)*(xval-3.0));
    }
  }

  // END TIMING
  std::chrono::time_point<std::chrono::steady_clock> end_time =
    std::chrono::steady_clock::now();
  std::chrono::duration<double> difference_in_time = end_time - begin_time;
  double difference_in_seconds = difference_in_time.count();

  // Print the integral.
  printf("The integral of the first function is %.15f\n", sum);

  // Find out how many processes there are.
  int num_threads = -1;
  #pragma omp parallel shared(num_threads)
  {
    if (omp_get_thread_num() == 0)
      num_threads = omp_get_num_threads();
  }

  // Print the timing.
  printf("With %d processes, this took %.15f seconds.\n", num_threads, difference_in_seconds);


  return 0;
}

