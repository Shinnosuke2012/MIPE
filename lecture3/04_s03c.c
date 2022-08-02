/* 数値積分（台形公式）による格子比熱計算（デバイモデル） */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define R  8.31447
#define QD  428  // Debye temperature of Al
#define EPS  1.E-6
#define GNUPLOT  "/usr/bin/gnuplot"  // gnuplotのパス

double func(double x){  // 関数の宣言：被積分関数
  return x*x*x*x*exp(x)/((exp(x)-1.)*(exp(x)-1.));
}

int main(){
  int n,i,j;
  double t,xmax,cv,a,b,fa,fb,s,h;
  FILE *fp,*pipe;

  fp=fopen("cv-Al.dat","w");

  printf("\nCalculating specific heat, Cv, of Al.\n\n");

  for(j=1;j<=1000;j++){ // 1[K]から1000[K]まで1[K]間隔で繰り返し
    t = (double)j; // Temperature, t/K
    xmax = QD/t; // 積分区間の上限
    n = 1000; // 分割数
    h = xmax/(double)n;
    a=0.; //積分区間の下限
    fa = func(a+EPS); // (x>0)：x=0では計算できない．
    s=0.;
    for(i=0;i<(n-1);i++){  // 一歩手前まで
      b = a + h;
      fb = func(b);
      s = s + (fa+fb)*h/2.; // 台形の面積
      a = b; //右端⇒左端に更新
      fa = fb;
    }
    b = xmax; // 最後は積分区間の上限
    fb = func(b);
    s = s + (fa+fb)*(b-a)/2.; // 台形の面積の積算
    cv = 9.*R*(t/QD)*(t/QD)*(t/QD)*s; //比熱：デバイの近似式
    printf("T= %6.1f , Cv= %8.4f \n",t,cv);
    fprintf(fp,"%6.1f  %8.4f\n",t,cv);
  }
  fclose(fp);

  // 関数をgnuplotで画面に表示し，pngファイルに出力する．
  if((pipe=popen(GNUPLOT " -persist","w"))==NULL){
    printf("Cannot open the pipe.\n");
    exit(1);  // 異常終了
  }

  fprintf(pipe,"set title \"Specific Heat of Al\"\n");
  fprintf(pipe,"set xzeroaxis\n");
  fprintf(pipe,"set xlabel \"T /K\"\n");
  fprintf(pipe,"set xrange [0:1100]\n");
  fprintf(pipe,"set xtics 100\n");
  fprintf(pipe,"set mxtics 2\n");
  fprintf(pipe,"set yzeroaxis\n");
  fprintf(pipe,"set ylabel \"Specific Heat / J/mol.K\"\n");
  fprintf(pipe,"set yrange [0:30]\n");
  fprintf(pipe,"set ytics 5\n");
  fprintf(pipe,"set mytics 5\n");
  fprintf(pipe,"set size square\n");

  fprintf(pipe,"plot \"cv-Al.dat\" with lines\n");
  fflush(pipe);  // バッファを掃き出す

  fprintf(pipe,"set term png \n");
  fprintf(pipe,"set output \"cv-Al.png\"\n");
  fprintf(pipe,"replot\n");
  fflush(pipe);  // バッファを掃き出す
  pclose(pipe);

  printf("\nProgram was completed.\n\n");

  exit(0);
}

