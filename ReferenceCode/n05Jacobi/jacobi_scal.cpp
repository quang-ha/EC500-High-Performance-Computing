
#include <stdio.h>
#include <math.h>

// 1D length
#define N 512

// Maximum number of iterations
#define ITER_MAX 100000000

// How often to check the relative residual
#define RESID_FREQ 1000 

// The residual
#define RESID 1e-6

double magnitude(double* T);
void jacobi(double* T, double* b, double* tmp);
double getResid(double* T, double* b);

int main(int argc, char** argv)
{
  int i,totiter;
  int done = 0;
  double* T = new double[N+1];
  double* Ttmp = new double[N+1];
  double* b = new double[N+1];
  double bmag, resmag;

  for (i=0;i<N;i++) { T[i] = 0.0; Ttmp[i] = 0.0; b[i] = 0.0; }
  b[N/2] = 1.0;
  //Get magnitude of rhs
  bmag = magnitude(b);
  printf("bmag: %.8e\n", bmag);

  for (totiter=RESID_FREQ;totiter<ITER_MAX && done==0;totiter+=RESID_FREQ)
  {
    // do RESID_FREQ jacobi iterations
    jacobi(T, b, Ttmp);

    resmag = getResid(T, b);

    printf("%d res %.8e bmag %.8e rel %.8e\n", totiter, resmag, bmag, resmag/bmag);
    if (resmag/bmag < RESID) { done = 1; }
  }

  delete[] T;
  delete[] Ttmp;
  delete[] b;

  return 0;
}

double magnitude(double* T)
{
   int i;
   double bmag;

   i = 0;
   bmag = 0.0;  
   for (i = 1; i<N; i++)
   {
     bmag = bmag + T[i]*T[i];
   }
   
   return sqrt(bmag);
}

void jacobi(double* T, double* b, double* tmp)
{
  int iter,i;

  iter = 0; i = 0;

  for (iter=0;iter<RESID_FREQ;iter++)
  {
    #pragma omp for
    for (i=1;i<N;i++)
    {
      tmp[i] = 0.5*(T[i+1]+T[i-1]) + b[i];
    }

    #pragma omp for
    for (i=1;i<N;i++)
    {
      T[i] = tmp[i];
    }
  }
}

double getResid(double* T, double* b)
{
  int i;
  double localres,resmag;

  i = 0;
  localres = 0.0;
  resmag = 0.0;

  for (i=1;i<N;i++)
  {
    localres = (b[i] - T[i] + 0.5*(T[i+1] + T[i-1]));
    localres = localres*localres;
    resmag = resmag + localres;
  }

  resmag = sqrt(resmag);

  return resmag;
}

