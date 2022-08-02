/* Find T point where G_solid = G_liquid using newton methods */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define R 8.31447
#define WL 3. * R *(60. - 90.)
#define WS 3. * R *(45. - 60.)
#define EPS 1.0E-6 // threshhold

#define GNUPLOT "C:/PROGRA~1/gnuplot/bin/gnuplot"

double f(double T, double x){ // function
    return (1250. * R - R * T) * (1. - x) + (750. * R - R * T) * x + (WL - WS) * (1. - x) * x;
}

int main(){
    FILE *pipe;

    pipe = popen(GNUPLOT " -persist","w");

    if (NULL==pipe){
        printf("Cannot open the pipe to GNUPLOT. \n");
        exit(1);
    }

    int n, i, j;
    double x,T0, T1, T2, dT, fT, dfT;
    FILE *file;
    file = fopen("C0TB1060-6-2.txt","w");

    n = 1000000;
    x = 0.01;
    T0 = 750.;
    T2 = T0;

    for (j=0;j<=100;j++){
        x = 0. + 0.01*j;

        if (x<=0.){
            x = 0. + 0.01;
        }

        if (x>=1.){
            x = 1. - 0.01;
        }


        do { // newton method
            i++;
            T1 = T2;
            fT = f(T1, x);
            dfT = -R;
            dT = -fT / dfT;
            T2 = T1 + dT;
            if (T2 <= 750.){
                T2 = 750. - EPS;
            }

            if (T2 >= 1250.){
                T2 = 1250. - EPS;
            }

        } while ((n > i) && (EPS < fabs(dT)));

        if (EPS < fabs(dT)){
            printf("\nDoesn't converge\n");
            exit(1);
        }

        printf("RESULT\n");
        printf("x0 = %f\n", T0);
        printf("Max_iteration = %d\n", i);
        printf("x = %.5f\n",x);
        printf("T = %f\n", T2);
        printf("------------------------------------------------");

        fprintf(file,"%.5f  %8.4f\n",x,T2);

    }
    fclose(file);

    //create graph
    fprintf(pipe,"set title \"Gibbs Free Energy x vs T \"\n");
    fprintf(pipe,"set xzeroaxis \n");
    fprintf(pipe,"set xlabel \"x\"\n");
    fprintf(pipe,"set ylabel \"T\"\n");
    fprintf(pipe,"plot \"C0TB1060-6-2.txt\" with lines\n");
    fflush(pipe);
    fprintf(pipe,"set term png \n"); 
    fprintf(pipe,"set output \"C0TB1060-6-2.png\"\n");
    fprintf(pipe,"replot \n");
    fflush(pipe); 
    pclose(pipe);
    exit(0);
}