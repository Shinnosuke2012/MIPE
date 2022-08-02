#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define R 8.31447
#define QD 1160
#define ESP 1.0E-6

#define GNUPLOT "C:/PROGRA~1/gnuplot/bin/gnuplot"

double func(double x){
    return x*x*x*x*exp(x)/((exp(x) - 1.)*(exp(x) - 1.));
    //f(x) = x^4*exp(x)/(exp(x) - 1)^2
}

int main(){
    //setting of gnuplot
    FILE *pipe;

    pipe = popen(GNUPLOT " -persist","w");

    if (NULL==pipe){
        printf("Cannot open the pipe to GNUPLOT. \n");
        exit(1);
    }

    int n,i,j;
    double t,xmax,cv,a,b,fa,fb,h,s;
    FILE *file;
    file = fopen("CV.dat","w");
    
    //conduct integration 1000 times
    for (j=1;j<=1000;j++){
        printf("Calculation of Cv \n");
        n = 1000;
        t = (double)j ;
        xmax = QD/t;
        h = xmax/(double)n; //width of each part
        a = 0.; //left side
        fa = func(a + ESP);
        s = 0.; //sum of area
        for (i=0;i<(n-1);i++){
            b = a + h;
            fb = func(b);
            s = s + (fa + fb)*h/2.; //calculating area
            a = b; //updating values of a
            fa = fb; //updating values of fa
        }
        //last one loop
        b = xmax;
        fb = func(b);
        s = s + (fa + fb)*(b-a)/2.;
        cv = 9.*R*(t/QD)*(t/QD)*(t/QD)*s;
        printf("T= %6.1f , Cv= %8.4f \n",t,cv);
        fprintf(file,"%6.1f  %8.4f\n",t,cv);
    }
    fclose(file);

    //create graph
    fprintf(pipe,"set title \"CV(Be) 0<x<=Q_D/T\"\n");
    fprintf(pipe,"set xzeroaxis \n");
    fprintf(pipe,"set xlabel \"T\"\n");
    fprintf(pipe,"set ylabel \"Cv(T)\"\n");
    fprintf(pipe,"plot \"CV.dat\" with lines\n");
    fflush(pipe);
    fprintf(pipe,"set term png \n"); 
    fprintf(pipe,"set output \"C0TB1060-3c.png\"\n");
    fprintf(pipe,"replot \n");
    fflush(pipe); 
    pclose(pipe);
    exit(0);
}