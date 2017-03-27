/*======================================================================================
Rich Brower Sat May 28 00:23:17 EDT 2011

C program based on simple FMV code of  S. F. McCormick, Multigrid Methods, Frontiers in Applied! Mathematics, 
vol. 3, SIAM Books, Philadelphia, 1987.The code is intentionally put into a single file with no input parameters 
to keep is concise. Of course a full code may have more traditional C structures!

We solve the 2-d Laplace problem:    A phi = b  

 (A phi)((x,y) = [4 phi(x,y) - phi(x+1,y) - phi(x-1,y) - phi(x,y+1)  -phi(x,y+1)]/a^2 + m^2 phi(x,y) = b(x,y)

 Multiply by scale = 1/(4 + a^2 m^2)

     phi  =  (1 - scale*A) phi +  scale*b = phi + res
          =     scale * (phi(x+1,y) + phi(x-1,y) + phi(x,y+1) + phi(x,y+1))  +  a^2 scale*b(x,y)

where we use rescaled: res =  a^2 scale b - scale* A phi

with scale(lev) = 1/(4 + pow(2,lev)^2 m^2)      or  the lattice spacing is   a(lev) = pow(2,lev) 

So the code is really sovling the new matrix iteration: 
    
      phi(x,y) = [(1- scale(lev) * A)phi](x,y) + res(x,y)   
        
               =  scale(lev) * (phi(x+1,y) + phi(x-1,y) + phi(x,y+1) + phi(x,y+1)) + res

At present relex iteration does Gauss Seidel. Can change to Gauss Jacobi or Red Black.
======================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>


typedef struct{
    int N;
    int Lmax;
    int size[20];
    double a[20];
    double m;
    double scale[20];
  } param_t;

void relax(double *phi, double *res, int lev, int niter, param_t p);
void proj_res(double *res_c, double *rec_f, double *phi_f, int lev,param_t p);
void inter_add(double *phi_f, double *phi_c, int lev,param_t p);
double GetResRoot(double *phi, double *res, int lev, param_t p);

int main()
{  
  double *phi[20], *res[20];
  param_t p;
  int nlev;
  int i,lev;
  
  //set parameters________________________________________
  p.Lmax = 7; // max number of levels
  p.N = 2*(int)pow(2,p.Lmax);  // MUST BE POWER OF 2
  p.m = 0.01;
  nlev = 5; // NUMBER OF LEVELS:  nlev = 0 give top level alone 
  if(nlev  > p.Lmax){ 
    printf("ERROR More levels than available in lattice! \n");
    return 0; }
  
  printf("\n V cycle for %d by %d lattice with nlev = %d out of max  %d \n", p.N, p.N, nlev, p.Lmax); 
  
  // initialize arrays__________________________________
  p.size[0] = p.N;
  p.a[0] = 1.0;
  p.scale[0] = 1.0/(4.0 + p.m*p.m);
  
  for(lev = 1;lev< p.Lmax+1; lev++) {
    p.size[lev] = p.size[lev-1]/2;
    p.a[lev] = 2.0 * p.a[lev-1];
    // p.scale[lev] = 1.0/(4.0 + p.m*p.m*p.a[lev]*p.a[lev]);
     p.scale[lev] = 1.0/(4.0 + p.m*p.m);
  }
  
  for(lev = 0;lev< p.Lmax+1; lev++)
    {
      phi[lev] = (double *) malloc(p.size[lev]*p.size[lev] * sizeof(double));
      res[lev] = (double *) malloc(p.size[lev]*p.size[lev] * sizeof(double));
      for(i = 0;i< p.size[lev]*p.size[lev];i++)
	{
	  phi[lev][i] = 0.0;
          res[lev][i] = 0.0;
	};
    }  
  
  res[0][p.N/2 + (p.N/2)*p.N] = 1.0*p.scale[0];  //unit point source in middle of N by N lattice 
  
  // iterate to solve_____________________________________
  double resmag = 1.0; // not rescaled.
  int ncycle = 0; 
  int n_per_lev = 10;
  resmag = GetResRoot(phi[0],res[0],0,p);
  printf("At the %d cycle the mag residue is %g \n",ncycle,resmag);
 
  // while(resmag > 0.00001 && ncycle < 10000)
   while(resmag > 0.00001)
    { 
      ncycle +=1; 
      for(lev = 0;lev<nlev; lev++)   //go down 
	{    
       relax(phi[lev],res[lev],lev, n_per_lev,p); // lev = 1, ..., nlev-1  
        proj_res(res[lev + 1], res[lev], phi[lev], lev,p);    // res[lev+1] += P^dag res[lev]
	}

      for(lev = nlev;lev >= 0; lev--)  //come up
	{ 
  	  relax(phi[lev],res[lev],lev, n_per_lev,p);   // lev = nlev -1, ... 0;
	  if(lev > 0) inter_add(phi[lev-1], phi[lev], lev, p);   // phi[lev-1] += error = P phi[lev] and set phi[lev] = 0;
	}
      resmag = GetResRoot(phi[0],res[0],0,p);
      printf("At the %d cycle the mag residue is %g \n",ncycle,resmag);
    }
  
  return 0;
}

void relax(double *phi, double *res, int lev, int niter, param_t p)
{  
  int i, x,y;
   int L;
   L  = p.size[lev];
  
  for(i=0; i<niter; i++)    
    for(x = 0; x < L; x++)
      for(y = 0; y < L; y++)
	{
	  phi[x + y*L] = res[x + y*L] 
	    + p.scale[lev] * (phi[(x+1)%L + y*L] + phi[(x-1+L)%L + y*L] 
				 +  phi[x + ((y+1)%L)*L]  + phi[x + ((y-1+L)%L)*L]);
       	}

  return;    
}

void proj_res(double *res_c, double *res_f, double *phi_f,int lev,param_t p)
{  
  int L, Lc, f_off, c_off, x, y;
  L = p.size[lev];
  double r[L*L]; // temp residue
  Lc = p.size[lev+1];  // course level
  
  //get residue
  for(x = 0; x< L; x++)
    for(y = 0; y< L; y++)
      r[x + y*L] = res_f[x + y*L] -  phi_f[x + y*L]  
	+ p.scale[lev]*(phi_f[(x+1)%L + y*L] + phi_f[(x-1+L)%L + y*L] + phi_f[x + ((y+1)%L)*L]  + phi_f[x + ((y-1+L)%L)*L]);
  
  //project residue
  for(x = 0; x< Lc; x++)
    for(y = 0; y< Lc; y++)
      res_c[x + y*Lc] = 0.25*(r[2*x + 2*y*L]  + r[(2*x + 1)%L + 2*y*L] + r[2*x + ((2*y+1))%L*L] + r[(2*x+1)%L + ((2*y+1)%L)*L]);

  return;
}

void inter_add(double *phi_f,double *phi_c,int lev,param_t p)
{  
  int L, Lc, x, y;
  Lc = p.size[lev];  // coarse  level
  L = p.size[lev-1]; 
  
  for(x = 0; x< Lc; x++)
    for(y = 0; y<Lc; y++)
      {
	phi_f[2*x  + 2*y*L]              += phi_c[x + y*Lc];
	phi_f[(2*x + 1)%L   + 2*y*L]     += phi_c[x + y*Lc];
	phi_f[2*x   + ((2*y+1))%L*L]     += phi_c[x + y*Lc];
	phi_f[(2*x+1)%L + ((2*y+1)%L)*L] += phi_c[x + y*Lc];
      }
  //set to zero so phi = error 
  for(x = 0; x< Lc; x++)
    for(y = 0; y<Lc; y++)
      phi_c[x + y*L] = 0.0;
  
  return;
}

double GetResRoot(double *phi, double *res, int lev, param_t p)
{ //true residue
  int i, x,y;
  double residue;
  double ResRoot = 0.0;
  int L;
  L  = p.size[lev];
  
  for(x = 0; x < L; x++)
    for(y = 0; y<L; y++){
      residue = res[x + y*L]/p.scale[lev] - phi[x + y*L]/p.scale[lev]  
	+ (phi[(x+1)%L + y*L] + phi[(x-1+L)%L + y*L] 
		   +  phi[x + ((y+1)%L)*L]  + phi[x + ((y-1+L)%L)*L]);
      ResRoot += residue*residue; // true residue
    }

  return sqrt(ResRoot);    
}
