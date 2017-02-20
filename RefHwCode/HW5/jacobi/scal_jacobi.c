
#include <stdio.h>
#include <math.h>

// 1D length
#define N 2048

// Maximum number of iterations
#define ITER_MAX 1000000

// How often to check the relative residual
#define RESID_FREQ 1000 

// The residual
#define RESID 1e-6

double magnitude(double* x);
void jacobi(double* x, double* b, double* tmp);
double getResid(double* x, double* b);

int main(int argc, char** argv)
{
   int i,totiter;
   int done = 0;
   double x[N], xtmp[N], b[N]; 
   double bmag, resmag;

   for (i=0;i<N;i++) { x[i] = 0.0; xtmp[i] = 0.0; b[i] = 0.0; }
   b[N/2] = 1.0;
   //Get magnitude of rhs
   bmag = magnitude(b);
   printf("bmag: %.8e\n", bmag);

   for (totiter=RESID_FREQ;totiter<ITER_MAX && done==0;totiter+=RESID_FREQ)
   {

      // do RESID_FREQ jacobi iterations
      jacobi(x, b, xtmp);

      resmag = getResid(x, b);

      printf("%d res %.8e bmag %.8e rel %.8e\n", totiter, resmag, bmag, resmag/bmag);
      if (resmag/bmag < RESID) { done = 1; }
   }

   
   return 0;
}

double magnitude(double* x)
{
   int i;
   double bmag;

   i = 0;
   bmag = 0.0;  
   for (i = 1; i<N-1; i++)
   {
     bmag = bmag + x[i]*x[i];
   }
   
   return sqrt(bmag);
}

void jacobi(double* x, double* b, double* tmp)
{
   int iter,i;

   iter = 0; i = 0;

   for (iter=0;iter<RESID_FREQ;iter++)
   {
      for (i=1;i<N-1;i++)
      {
         tmp[i] = 0.5*(x[i+1]+x[i-1]) + b[i];
      }

      for (i=1;i<N-1;i++)
      {
         x[i] = tmp[i];
      }
   }
}

double getResid(double* x, double* b)
{
   int i;
   double localres,resmag;

   i = 0;
   localres = 0.0;
   resmag = 0.0;

   for (i=1;i<N-1;i++)
   {
      localres = (b[i] - x[i] + 0.5*(x[i+1] + x[i-1]));
      localres = localres*localres;
      resmag = resmag + localres;
   }

   resmag = sqrt(resmag);

   return resmag;
}

