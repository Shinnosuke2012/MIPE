// Monte-Carlo methods

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define NMAX 1E7
#define PI 3.141
#define GNUPLOT "C:/PROGRA~1/gnuplot/bin/gnuplot"  // gnuplotのパス

int main(){
  int seed,i,j,c,step;
  double x,y,z,rr,v,pi;
  FILE *fp,*pipe;
  
  fp=fopen("C0TB1060-9-2.txt","w");

  seed = time(NULL);  // 擬似乱数の種
  srand((unsigned int)seed);  // 擬似乱数の初期化

  c = 0;  // 擬似乱数の点(x,y,z)が半径sin(x)以上半径1の球内に入った回数cの初期化
  step = 50;  // データを保存するstepの初期値

  for(i=0 ; i<NMAX ; i++){
    x = 2.*(PI/2.)*(double)rand()/RAND_MAX -(PI/2.); // -1≦x≦1の擬似乱数
    y = 2.*(double)rand()/RAND_MAX -1.; // -1≦y≦1の擬似乱数
    z = 2.*(double)rand()/RAND_MAX -1.; // -1≦z≦1の擬似乱数
    rr = y*y + z*z;
    if((sin(x)*sin(x) <= rr) && (rr<=1.)) c++;
    //ログ用
    if(i+1 == step){
      v = 4.*PI*(double)c/(double)(i+1.);  // 球の体積
      printf("\nTrial numbers:n= %d  /  Volume: v= %9.7f \n",i+1,v);
      fprintf(fp,"%d  %9.7f \n",i+1,v);
      step *= 2;
    }
  }

  printf("\nTrial numbers: n= %8.0f  /  Volume:v= %9.7f \n\n",NMAX,v);
  fprintf(fp,"%8.0f  %9.7f \n",NMAX,v);

  fclose(fp);

/* 計算結果をgnuplotで画面に表示し，pngファイルに出力する． */
  if((pipe=popen(GNUPLOT " -persist","w"))==NULL){
    fprintf(stderr,"パイプが開けません\n");
    exit(1);
  }

  fprintf(pipe,"set title \"Monte-Calro methods\"\n"); // グラフのタイトル
  fprintf(pipe,"set xlabel \"Trial number\"\n");  // x軸のラベル
  fprintf(pipe,"set ylabel \"Volume of Rotating body\"\n");  // y軸のラベル
  fprintf(pipe,"set logscale x\n");  // x軸を対数表示
  fprintf(pipe,"set xrange [10:2E7]\n");  // x軸の範囲
  fprintf(pipe,"set yrange [3.0:6.5]\n");  // y軸の範囲
  fprintf(pipe,"set ytics 0.2\n");  // y軸メモリの間隔
  fprintf(pipe,"set mytics 2\n");  // y軸メモリ間の分割数
  fprintf(pipe,"set size square\n");  // グラフの縦横比：正方形

  fprintf(pipe,"plot \"C0TB1060-9-2.txt\" with linespoints \n");
  fflush(pipe);

  fprintf(pipe,"set term png \n"); // 出力先をpngに変更
  fprintf(pipe,"set output \"C0TB1060-9-2.png\"\n");  //pngファイル名
  fprintf(pipe,"replot \n");  // 再描画
  fflush(pipe);

  pclose(pipe);
  exit(0);
}

