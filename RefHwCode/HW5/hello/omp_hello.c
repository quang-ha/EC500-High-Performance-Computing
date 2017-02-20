#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
   int tid, nthreads;

   #pragma omp parallel shared(nthreads) private(tid)
   {
      tid = omp_get_thread_num();
      if (tid == 0)
      {
         nthreads = omp_get_num_threads();
      }

      #pragma omp barrier

      printf("Hello world from thread %d of %d!\n", tid, nthreads);
   }
   return 0;
}
