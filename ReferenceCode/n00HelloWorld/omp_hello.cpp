#include <omp.h>
#include <stdio.h>

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

  return 0;

}
