// A simple test file which demonstrates
// how to use timing routines in C++. For simplicity,
// we just implement a simple routine that adds a long
// array of numbers multiple times.
// This version uses MPI.

#include <iostream>
#include <chrono>
#include <mpi.h>

int main(int argc, char** argv)
{
  int world_size; // number of MPI processes
  int world_rank; // rank of MPI process
  char processor_name[MPI_MAX_PROCESSOR_NAME]; // name of processor
  int name_len; // length of name string.

  // Initialize MPI
  MPI_Init(&argc, &argv);

  // Get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  MPI_Get_processor_name(processor_name, &name_len);

  printf("Hello world from rank %d of %d! My name is %s!\n", world_rank, world_size, processor_name);

  // length of the array
  const int length = 10000000;

  // Yes, but what's the size of my array?
  const int my_length = length/world_size;

  // allocate three arrays.
  double* arr1 = new double[my_length];
  double* arr2 = new double[my_length];
  double* sum = new double[my_length];

  // fill the arrays with numbers
  // this intentionally doesn't do the same
  // thing as the OpenMP version---you have to
  // figure this out on the homework ;)
  for (int i = 0; i < my_length; i++)
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
    for (int i = 0; i < my_length; i++) {
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

  // Clean up 
  MPI_Finalize();

  // We did it!
  return 0;
}
