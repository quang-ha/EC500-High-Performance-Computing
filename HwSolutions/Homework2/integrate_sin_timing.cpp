
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

  // Beginning of interval 
  double a = 1.0;

  // End of interval
  double b = 2.0;

  // Number of sub-intervals.
  int N = 30000000;

  // My sub-intervals
  int my_N = N / world_size;

  double my_a = 1.0 + (b-a)/world_size*world_rank;
  double my_b = 1.0 + (b-a)/world_size*(world_rank+1);

  // Where we accumulate the approximate integral.
  double sum = 0.0;

  // Pre-compute the window width.
  double epsilon = (b-a)/((double)N);

  // BEGIN TIMING
  std::chrono::time_point<std::chrono::steady_clock> begin_time =
  std::chrono::steady_clock::now();

  // Perform the integral
  #pragma omp parallel for reduction(+:sum)
  for (int i = 0; i < my_N; i++)
  {
    sum += epsilon*sin(my_a + epsilon*i + epsilon*0.5);
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
    printf("The integral from %.8f to %.8f of sin(x) using %d intervals is %.15f\n", a, b, N, global_sum);

    // Print the timing.
    printf("With %d processes, this took %.15f seconds.\n", world_size, difference_in_seconds);
  }

  // finalize
  MPI_Finalize();

  return 0;
}

