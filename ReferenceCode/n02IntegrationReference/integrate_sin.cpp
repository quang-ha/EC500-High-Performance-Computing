
#include <cmath>
#include <stdio.h>
#include <chrono>

int main(int argc, char** argv)
{
  // Beginning of interval 
  double a = 1.0;

  // End of interval
  double b = 2.0;

  // Number of sub-intervals.
  int N = 30000000;

  // Where we accumulate the approximate integral.
  double sum = 0.0;

  // Pre-compute the window width.
  double epsilon = (b-a)/((double)N);

  // TIMING LINE 1: Get the starting timestamp. 
  std::chrono::time_point<std::chrono::steady_clock> begin_time =
    std::chrono::steady_clock::now();

  // Perform the integral
  for (int i = 0; i < N; i++)
  {
    sum += epsilon*sin(a + epsilon*i + epsilon*0.5);
  }

  // TIMING LINE 2: Get the ending timestamp.
  std::chrono::time_point<std::chrono::steady_clock> end_time =
    std::chrono::steady_clock::now();

  // TIMING LINE 3: Compute the difference.
  std::chrono::duration<double> difference_in_time = end_time - begin_time;
  //
  // TIMING LINE 4: Get the difference in seconds.
  double difference_in_seconds = difference_in_time.count();

  // Print the integral.
  printf("The integral from %.8f to %.8f of sin(x) using %d intervals is %.15f\n", a, b, N, sum);
  printf("This took %.8f seconds.\n", difference_in_seconds);

  return 0;
}

