/* Find T point where G_solid = G_liquid using newton methods */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define R 8.31447
#define WL 3. * R *(60. - 90.)
#define WS 3. * R *(45. - 60.)
#define EPS 1.0E-6 // threshhold

#define GNUPLOT "C:/PROGRA~1/gnuplot/bin/gnuplot"

double f(double x, double T){ // function
    return (1250. * R - R * T) * (1. - x) + (750. * R - R * T) * x + (WL - WS) * (1. - x) * x;
}

double df(double x) { // differentiation of function
    return -500. * R + (WL - WS) * (1. - 2. * x);
}

int main(){
    FILE *pipe;

    pipe = popen(GNUPLOT " -persist","w");

    if (NULL==pipe){
        printf("Cannot open the pipe to GNUPLOT. \n");
        exit(1);
    }

    int n, i, j;
    double x0, x1, x2, dx, fx, dfx, T;
    FILE *file;
    file = fopen("C0TB1060-6-1.txt","w");

    n = 1000;
    x0 = 0.05;
    T = 750.;
    x2 = x0;

    for (j=0;j<=50;j++){
        T = 750.1 + 10.*j;

        if (T<=750.){
            T = 750. + 0.1;
        }

        if (T>=1250.){
            T = 1250. - 0.1;
        }


        do { // newton method
            i++;
            x1 = x2;
            fx = f(x1, T);
            dfx = df(x1);
            dx = -fx / dfx;
            x2 = x1 + dx;
            if (x2 <= 0.){
                x2 = EPS;
            }

            if (x2 >= 1.){
                x2 = 1. - EPS;
            }

        } while ((n > i) && (EPS < fabs(dx)));

        if (EPS < fabs(dx)){
            printf("\nDoesn't converge\n");
            exit(1);
        }

        printf("RESULT\n");
        printf("x0 = %f\n", x0);
        printf("Max_iteration = %d\n", i);
        printf("T = %f\n",T);
        printf("x = %f\n", x2);
        printf("------------------------------------------------");

        fprintf(file,"%6.1f  %8.4f\n",T,x2);

    }
    fclose(file);

    //create graph
    fprintf(pipe,"set title \"Gibbs Free Energy T vs x \"\n");
    fprintf(pipe,"set xzeroaxis \n");
    fprintf(pipe,"set xlabel \"T\"\n");
    fprintf(pipe,"set ylabel \"x\"\n");
    fprintf(pipe,"plot \"C0TB1060-6-1.txt\" with lines\n");
    fflush(pipe);
    fprintf(pipe,"set term png \n"); 
    fprintf(pipe,"set output \"C0TB1060-6-1.png\"\n");
    fprintf(pipe,"replot \n");
    fflush(pipe); 
    pclose(pipe);
    exit(0);
}