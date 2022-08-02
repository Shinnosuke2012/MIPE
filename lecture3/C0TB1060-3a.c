#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GNUPLOT "C:/PROGRA~1/gnuplot/bin/gnuplot"

int main(){
    FILE *pipe;

    pipe = popen(GNUPLOT " -persist","w");

    if (NULL==pipe){
        printf("Cannot open the pipe to GNUPLOT. \n");
        exit(1);
    }

    fprintf(pipe,"set title \"f(x) = x^4*exp(x)/(exp(x)-1)^2\"\n");
    fprintf(pipe,"set xzeroaxis \n");
    fprintf(pipe,"set xlabel \"x\"\n");
    fprintf(pipe,"set xrange [0:20]\n");
    fprintf(pipe,"set yzeroaxis \n");
    fprintf(pipe,"set ylabel \"y\"\n");
    fprintf(pipe,"set size square\n");
    fprintf(pipe,"set yrange[0:6] \n");

    fprintf(pipe,"f(x) = (x**4 * exp(x))/(exp(x) - 1)**2 \n");
    fprintf(pipe,"plot f(x) \n");
    fflush(pipe);

    fprintf(pipe,"set term png \n"); 
    fprintf(pipe,"set output \"C0TB1060-3a.png\"\n");
    fprintf(pipe,"replot \n");

    fflush(pipe);

    pclose(pipe);
}