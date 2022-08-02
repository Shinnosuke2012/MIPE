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

    fprintf(pipe,"set title \"free energy diagram\"\n");
    fprintf(pipe,"set xzeroaxis \n");
    fprintf(pipe,"set xlabel \"x_B\"\n");
    fprintf(pipe,"set xrange [0:1]\n");
    fprintf(pipe,"set yzeroaxis \n");
    fprintf(pipe,"set ylabel \"Gibbs Free Energy, G_m/KJ*mol^-1\"\n");
    fprintf(pipe,"set size square\n");

    fprintf(pipe,"T = 1100\n");
    fprintf(pipe,"R = 8.31447\n");
    fprintf(pipe,"GLA = 1250*R - R*T \n");
    fprintf(pipe,"GLB = 750*R - R*T \n");
    //3digits of ID numbers
    fprintf(pipe,"WL = 25*R*60 \n");
    fprintf(pipe,"GSA = 0 \n");
    fprintf(pipe,"GSB = 0 \n");
    //3digits of ID numbers
    fprintf(pipe,"WS = 25*R*(150 - 60) \n");

    fprintf(pipe,"gl(x) = (GLA*(1.-x) + GLB*x + WL*x*(1. -x) + R*T*(x*log(x) + (1. -x)*log(1. -x)))/1000 \n");
    fprintf(pipe,"gs(x) = (GSA*(1.-x) + GSB*x + WS*x*(1. -x) + R*T*(x*log(x) + (1. -x)*log(1. -x)))/1000 \n");

    fprintf(pipe,"set label 1 at graph 0.4,0.3 \"GL\"\n");
    fprintf(pipe,"set label 2 at graph 0.5,0.6 \"GS\"\n");
    fprintf(pipe,"set label 3 at graph 0.2,0.8 \"T = 1000K\"\n");
    fprintf(pipe,"plot gl(x),gs(x) \n");
    fflush(pipe);

    fprintf(pipe,"set term png \n"); 
    fprintf(pipe,"set output \"C0TB1060-2.png\"\n");
    fprintf(pipe,"replot \n");

    fflush(pipe);

    pclose(pipe);
}