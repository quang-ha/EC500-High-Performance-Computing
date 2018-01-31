// Based on the tutorial from mpitutorial.com/tutorials/mpi-hello-world/

#include <mpi.h>
#include <stdio.h>

#define ITER_MAX 1000

int  main(int argc, char** argv)
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

   // Clean up
   MPI_Finalize();
   return 0;
}
