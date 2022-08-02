/* Create binary phase diagram */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define R 8.31447
#define WL 4. * R *(60. - 90.)
#define WS 2. * R *(45. - 60.)
#define EPS 1.0E-6

#define GNUPLOT "C:/PROGRA~1/gnuplot/bin/gnuplot"

double gl(double x,double t){
  return (1250.*R-R*t)*(1.-x)+(750.*R-R*t)*x+WL*(1.-x)*x+R*t*(x*log(x)-(1.-x)*log(1.-x));
}

double gs(double x,double t){
  return +WS*(1.-x)*x+R*t*(x*log(x)-(1.-x)*log(1.-x));
}

double g(double y,double z,double t){
  return ((1250.*R-R*t)+WL*y*y+R*t*log(1.-y))-(WS*z*z+R*t*log(1.-z));
}

double h(double y,double z,double t){
  return ((750.*R-R*t)+WL*(1.-y)*(1.-y)+R*t*log(y))-(WS*(1.-z)*(1.-z)+R*t*log(z));
}

double dgdy(double y,double z,double t){
  return 2.*WL*y -R*t/(1.-y);
}

double dgdz(double y,double z,double t){
  return -2.*WS*z +R*t/(1.-z);
}

double dhdy(double y,double z,double t){
  return -2.*WL*(1.-y) +R*t/y;
}

double dhdz(double y,double z,double t){
  return 2.*WS*(1.-z) -R*t/z;
}

int main(){
    int i,j,n,nx;
    double t0,det,x,dx,x0,y0,y1,y2,dy,z0,z1,z2,dz,dgy,dgz,dhy,dhz;
    FILE *ft0,*fl,*fs,*pipe;

    ft0 = fopen("ft0.txt","w");
    fl = fopen("fl.txt","w");
    fs = fopen("fs.txt","w");

    n = 100;
    dx = 0.01;
    nx = (int)1./dx;

    for (j=0;j<=nx;j++){
      x = dx*(double)j;

      if (x<=0.){
        x = dx/10.;
      }
      if (x>=1.){
        x = 1. - dx/10.;
      }

      t0 = ((WL - WS)*(1. - x)*x +1250.*R*(1. - x) + 750.*R*x)/R;

      //output results
      printf("fraction:x = %.5f\n",x);
      printf("T0:T = %8.4f\n",t0);

      //write results in ft0 file
      fprintf(ft0,"%.5f  %8.4f\n",x,t0);

      if (x < 0.5){
        x0 = x/5.;
      }
      else {
        x0 = (1 - x)/5.;
      }

      //set initial values
      if ((gl(x + EPS,t0) - gs(x + EPS,t0))<0){
        y0 = x + x0;
        z0 = x - x0;
      }

      else {
        y0 = x - x0;
        z0 = x + x0;
      }

      y2 = y0;
      z2 = z0;

      //iteration num
      i = 0;

      do {
        i = i + 1;

        y1 = y2;
        z1 = z2;

        dgy = dgdy(y1,z1,t0);
        dgz = dgdz(y1,z1,t0);
        dhy = dhdy(y1,z1,t0);
        dhz = dhdz(y1,z1,t0);

        det = dgy*dhz - dgz*dhy;
            
        dy = (-dhz*g(y1,z1,t0) + dgz*h(y1,z1,t0))/det;
        dz = (dhy*g(y1,z1,t0) - dgy*h(y1,z1,t0))/det;

        y2 = y1 + dy;
        z2 = z1 + dz;

        // make restrictions
        if (y2<=0.){
          y2 = EPS;
        }
        if (y2>=1.){
          y2 = 1. - EPS;
        }
        if (z2<=0.){
          z2 = EPS;
        }
        if (z2 >= 1.){
          z2 = 1. - EPS;
        }

      } while ((i<n)&&((fabs(dy)>EPS)||(fabs(dz)>EPS)));

      //outputs results
      printf("Iteration num: N = %d \n",i);
      printf("Temperature: T= %8.4f \n",t0);
      printf("Eqibllium fraction: %.5f  %.5f \n",y2,z2);

      //write results in file
      fprintf(fl,"%.5f  %8.4f\n",y2,t0);
      fprintf(fs,"%.5f  %8.4f\n",z2,t0);
      printf("==============================================================\n");
    }

    fclose(ft0);
    fclose(fl);
    fclose(fs);

    pipe = popen(GNUPLOT " -persist","w");

    if (NULL==pipe){
      printf("Cannot open the pipe to GNUPLOT. \n");
      exit(1);
    }

        //create graph
    fprintf(pipe,"set title \"binary phase diagram \"\n");
    fprintf(pipe,"set xzeroaxis \n");
    fprintf(pipe,"set xlabel \"x_B\"\n");
    fprintf(pipe,"set ylabel \"T\"\n");
    fprintf(pipe,"plot \"ft0.txt\"with lines lw 2 dt 5 lc rgb 'black',\"fs.txt\"with lines lw 3 lc rgb 'black',\"fl.txt\"with lines lw 3 lc rgb 'black'\n");
    fflush(pipe);
    fprintf(pipe,"set term png \n"); 
    fprintf(pipe,"set output \"C0TB1060-e1.png\"\n");
    fprintf(pipe,"replot \n");
    fflush(pipe); 
    pclose(pipe);
    exit(0);
}