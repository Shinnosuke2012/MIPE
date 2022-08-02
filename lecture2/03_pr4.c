#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GNUPLOT "C:/PROGRA~1/gnuplot/bin/gnuplot"

int main(){
  FILE *pipe;


  pipe = popen(GNUPLOT " -persist","w");
  if(NULL==pipe){
    printf("Cannot open the pipe to GNUPLOT.\n");
    exit(1); 
  }

  fprintf(pipe,"set title \"y = exp(x)-x*x \"\n");  

  fprintf(pipe,"f(x) = exp(x)-x*x\n");  
  fprintf(pipe,"set xzeroaxis\n");  

  fprintf(pipe,"set xlabel \"x\"\n");  

  fprintf(pipe,"set xrange [-10:6]\n");  
  fprintf(pipe,"set xtics 2\n");  
  fprintf(pipe,"set mxtics 2\n");  

  fprintf(pipe,"set yzeroaxis\n"); 

  fprintf(pipe,"set ylabel \"y\"\n");  

  fprintf(pipe,"set yrange [-100:100]\n");  
  fprintf(pipe,"set ytics 20\n");  
  fprintf(pipe,"set mytics 2\n");  


  fprintf(pipe,"set size square\n"); 

  fprintf(pipe,"plot f(x)\n");  
  fflush(pipe);  

  fprintf(pipe,"set term png \n"); 
  fprintf(pipe,"set output \"fx.png\"\n");  

  fprintf(pipe,"replot \n");  

  fflush(pipe); 

  pclose(pipe);
}
