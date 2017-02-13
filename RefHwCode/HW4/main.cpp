#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// Assign a vector to a constant everywhere.
template <typename T> inline void constant(T* __restrict__ x, T val, int size)
{
  #pragma omp parallel for shared(x, val)
  for (int i = 0; i < size; i++)
  {
    x[i] = val;
  }
}

template <typename T> inline void caxpy(T a, T* __restrict__ x, T* __restrict__ y, int size)
{
  #pragma omp parallel for shared(a, x, y)
  for (int i = 0; i < size; i++)
  {
    y[i] = a*x[i] + y[i];
  }
}

template<typename T> inline T dot(T* __restrict__ v1, T* __restrict__ v2, int size)
{
  T res = static_cast<T>(0.0);
  #pragma omp parallel for shared(v1, v2) reduction (+:res)
  for (int i = 0; i < size; i++)
  {
    res = res + v1[i]*v2[i];
  }
  
  return res;
}

int main(int argc, char** argv)
{
  int nthreads, tid;
  
  int i;
  double a = 2.0;
  const int size = 1024*1024;
  double* x = new double[size];
  double* y = new double[size];
  double the_sum = 0.0;
  
  #pragma omp parallel private(nthreads, tid) shared(a, x, y)
  {
    tid = omp_get_thread_num();
    printf("Hello world from thread = %d!\n", tid);
    
    // Only master thread
    if (tid == 0)
    {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d.\n", nthreads);
    }
  }
  
  constant(x, 2.0, size);
  constant(y, 3.0, size);

  caxpy(a, x, y, size);

  the_sum = dot(x, y, size);

  printf("Result of dot product: %.8e\n", the_sum);

  return 0;
}
