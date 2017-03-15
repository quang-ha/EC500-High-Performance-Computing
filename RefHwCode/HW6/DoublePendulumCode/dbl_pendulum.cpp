/* Program which simulates the motion of a double pendulum
   by solving numerically the Lagrange equations with the
   Runge-Kutta algorithm.  This program writes on file the 
   evolution data. 
*/

#include <stdio.h>
#include <math.h>

int main()
{
  int nstep,step,npr,samplestep;
  double th1,th2,v1,v2,p1,p2,th1m,th2m,p1m,p2m;
  double s1,c1,s2,c2,h1, h2;
  double l=0.5, m=1, g=10; 
  double t, dt, tmax, tpr;
  double K,V,E;
  
  printf("\nEnter the initial values of theta1 and theta2 (in radians):  ");
  scanf("%lf%lf",&th1,&th2);
  printf("Enter the initial values of dtheta1/dt and dtheta2/dt:  ");
  scanf("%lf%lf",&v1,&v2);
  p1=m*l*l*(2*v1+v2*cos(th1-th2));
  p2=m*l*l*(v1*cos(th1-th2)+v2);
  K=m*l*l*(2*v1*v1+2*v1*v2*cos(th1-th2)+v2*v2);
  V=-m*g*l*(2*cos(th1)+cos(th2));
  E=K+V;
  printf("\nInitial energy:  %f\n\n",E);
  t=0;
  
  // Input parameters for Double Pendulum
  
  printf("Enter the total evolution time, the time step and the time\n");
  printf("interval between printouts:  ");
  scanf("%lf%lf%lf",&tmax,&dt,&tpr);
  nstep=tmax/dt;
  npr=nearbyint(tpr/dt);  
  printf("Data will be output at a resized time interval %f\n",npr*dt);
  printf("\n");

  //Define Outfile for Trace of Pendulum
  
  char filename[256];
  sprintf(filename, "Trace_th1=%4.2f_th2=%4.2f_v1=%4.2f_v2=%4.2f_tmax=%8.2f_dt=%8.6f_tsample=%8.6f.dat",th1, th2,v1,v2,tmax,dt,tpr);
  FILE *out = fopen(filename, "w");
  if(out == NULL) {
    fprintf(stderr, "Could not open file %s for writing\n", filename);
    return 0;
  }

  // Solve Coupled ODE's by  Runge-Kutta 
  step=0;
  samplestep =0;
  t=step*dt;  
  s1=sin(th1); c1=cos(th1); s2=sin(th2); c2=cos(th2);
  h1 = 1- cos(th1);  h2 = 2 -  cos(th1)- cos(th2);
 
   fprintf(out,"# Step   Time     sin1        cos1        sin2        cos2        h1          h2 \n");
   fprintf(out,"%d %7.4f %11.6f %11.6f %11.6f %11.6f %11.6f %11.6f\n",samplestep, t,s1,c1,s2,c2, h1, h2);

  while(t<tmax){

    v1=(p1-p2*cos(th1-th2))/(m*l*l*(2-cos(th1-th2)*cos(th1-th2)));
    v2=(-p1*cos(th1-th2)+2*p2)/(m*l*l*(2-cos(th1-th2)*cos(th1-th2)));
    p1m=p1+m*l*l*(-v1*v2*sin(th1-th2)-2*g*sin(th1))*dt/2;
    p2m=p2+m*l*l*(v1*v2*sin(th1-th2)-g*sin(th2))*dt/2;
    th1m=th1+v1*dt/2;
    th2m=th2+v2*dt/2;
    
    v1=(p1m-p2m*cos(th1m-th2m))/(m*l*l*(2-cos(th1m-th2m)*cos(th1m-th2m)));
    v2=(-p1m*cos(th1m-th2m)+2*p2m)/(m*l*l*(2-cos(th1m-th2m)*cos(th1m-th2m)));
    p1=p1+m*l*l*(-v1*v2*sin(th1m-th2m)-2*g*sin(th1m))*dt;
    p2=p2+m*l*l*(v1*v2*sin(th1m-th2m)-g*sin(th2m))*dt;
    th1=th1+v1*dt;
    th2=th2+v2*dt;
    
    step=step+1;
    t=step*dt;
    
    if(step%npr==0){
      samplestep +=1;
      s1=sin(th1); c1=cos(th1); s2=sin(th2); c2=cos(th2);
      h1 = 1- cos(th1);h2 = 2 - cos(th1) -cos(th2);
      fprintf(out,"%d  %7.4f %11.6f %11.6f %11.6f %11.6f %11.6f %11.6f\n",samplestep, t,s1,c1,s2,c2, h1, h2);
    }

  }

  K=m*l*l*(2*v1*v1+2*v1*v2*cos(th1-th2)+v2*v2);
  V=-m*g*l*(2*cos(th1)+cos(th2));
  E=K+V;
  printf("Final energy:  %f\n\n",E);

}
