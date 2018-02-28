
#include <cmath>
#include <stdio.h>
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

  // My sub-intervals. Only split in x direction.
  int my_N = N / world_size;

  double my_a = a + (b-a)/world_size*world_rank;
  double my_b = a + (b-a)/world_size*(world_rank+1);

  // Where we accumulate the approximate integral.
  double sum = 0.0;

  // Pre-compute the window width.
  double epsilon_x = (b-a)/((double)N);
  double epsilon_y = (d-c)/((double)N);

  // BEGIN TIMING
  std::chrono::time_point<std::chrono::steady_clock> begin_time =
  std::chrono::steady_clock::now();

  // Perform the integral
  // #pragma omp parallel for reduction(+:sum)
  for (int x = 0; x < my_N; x++)
  {
    for (int y = 0; y < N; y++)
    {
      double xval = my_a + epsilon_x*((double)x + 0.5);
      double yval = c + epsilon_y*((double)y + 0.5);
      sum += epsilon_x*epsilon_y*(xval*xval + yval*yval + (yval-1.0)*(yval-1.0)*(yval-1.0)*(xval-3.0));
    }
  }

  double global_sum = 0.0;
  MPI_Allreduce(&sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

  // END TIMING
  std::chrono::time_point<std::chrono::steady_clock> end_time =
    std::chrono::steady_clock::now();
  std::chrono::duration<double> difference_in_time = end_time - begin_time;
  double difference_in_seconds = difference_in_time.count();

  if (world_rank == 0)
  {
    // Print the process name.
    printf("Hello from %s\n", processor_name);

    // Print the integral.
    printf("The integral of the first function is %.15f\n", global_sum);

    // Print the timing.
    printf("With %d processes, this took %.15f seconds.\n", world_size, difference_in_seconds);
  }

  // finalize
  MPI_Finalize();

  return 0;
}

