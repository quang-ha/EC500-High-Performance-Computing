// A simple test file which demonstrates
// how to use timing routines in C++. For simplicity,
// we just implement a simple routine that adds a long
// array of numbers multiple times.
// This version uses OpenMP

#include <iostream>
#include <chrono>
#include <omp.h>

int main(int argc, char** argv)
{
  int nthreads = -1;
  int thread_id = -1;

  #pragma omp parallel shared(nthreads) private(thread_id)
  {
    thread_id = omp_get_thread_num();
    if (thread_id == 0)
      nthreads = omp_get_num_threads();
  
    // You need this to make sure every thread learns how many
    // threads there are in total before printing.
    #pragma omp barrier
  
    printf("Hello world from thread %d of %d!\n", thread_id, nthreads);
  }


  // length of the array
  const int length = 10000000;

  // allocate three arrays.
  double* arr1 = new double[length];
  double* arr2 = new double[length];
  double* sum = new double[length];

  // Fill the arrays with numbers
  for (int i = 0; i < length; i++)
  {
    arr1[i] = (double)i;
    arr2[i] = 3.14*((double)i);
    sum[i] = 0.0;
  }

  // TIMING LINE 1: Get the starting timestamp. 
  std::chrono::time_point<std::chrono::steady_clock> begin_time =
    std::chrono::steady_clock::now();

  // Perform the sums 100 times as a task.
  for (int t = 0; t < 100; t++) {
    #pragma omp parallel for 
    for (int i = 0; i < length; i++) {
      sum[i] = arr1[i] + arr2[i];
    }
  }

  // TIMING LINE 2: Get the ending timestamp.
  std::chrono::time_point<std::chrono::steady_clock> end_time =
    std::chrono::steady_clock::now();

  // TIMING LINE 3: Compute the difference.
  std::chrono::duration<double> difference_in_time = end_time - begin_time;

  // TIMING LINE 4: Get the difference in seconds.
  double difference_in_seconds = difference_in_time.count();

  // Print the time.
  printf("Simple addition took %.10f seconds.\n", difference_in_seconds);

  // Clean up
  delete[] arr1;
  delete[] arr2;
  delete[] sum;

  // We did it!
  return 0;
}
