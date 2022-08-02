/* 擬似乱数（pseudo-random numbers:prn）の作成と確認 
(1) 0～1までの擬似乱数をn個作成し，0.1間隔で擬似乱数の発生回数を調べる．
(2) 階級とその発生回数を画面に表示する．
(3) gnuplotを用いて，発生回数を棒グラフに表示する．
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define GNUPLOT "C:/PROGRA~1/gnuplot/bin/gnuplot"

int main(){
  int n,i,j,seed,f[10];
  int fstep,fmax;
  double prn,ca,cb,cm;
  FILE *fp,*pipe;
  
  for(i=0 ; i<10 ; i++) f[i]=0; // 擬似乱数の個数を数える配列の初期化
    
  seed = time(NULL); // 擬似乱数の種
  srand((unsigned int)seed); // 擬似乱数の初期化

  printf("\n RAND_MAX= %d\n",RAND_MAX); // RAND_MAX値の確認（2,147,483,647）

  printf("\n 作成する擬似乱数の個数：n を入力して下さい。\n");
  printf("   n= ");
  scanf("%d", &n);
  
  for(j=0 ; j<n ; j++){ // 擬似乱数(0.≦prn＜1.)の作成
    prn = (double)rand()/(RAND_MAX+1.); // 乱数発生（分母に1.を足しているのは何故？）
    i = (int)(prn*10.);  // 擬似乱数の値(0.≦prn＜1.)を配列の添字（0≦i≦9）に変換
    f[i]++; // 乱数の発生個数分布を調べるための配列
  }

  fp = fopen("12_frequency.dat","w");

  fmax = 0; // 乱数の発生個数の最大値の初期化
  printf("\n seed = %d\n\n",seed);  // 乱数の種値を表示
  
  for(i=0 ; i<10 ; i++){ // 擬似乱数の分布
    ca = (double)i/10.; // 階級下限
    cb = (double)(i+1)/10.; // 階級上限
    cm = (ca+cb)/2.; // 階級中間値（gnuplotのx軸値）
    printf(" %3.1f - %3.1f / f[%d]=%d\n",ca,cb,i,f[i]); // 画面出力
    fprintf(fp,"%4.2f  %d\n",cm,f[i]); // ファイル出力（gnuplotで利用）
    if(f[i]>fmax) fmax = f[i]; // 乱数の発生個数の最大値（gnuplot縦軸上限値用）
  }

  fclose(fp);


// 計算結果をgnuplotで画面に表示し，pngファイルに出力する．
  if((pipe=popen(GNUPLOT " -persist","w"))==NULL){
    fprintf(stderr,"パイプが開けません\n");
    exit(1);
  }

  fstep = (int)(n/100.); // y軸メモリの間隔

  fprintf(pipe,"set title \"Pseudo-random numbers : n = %d\"\n",n); // グラフのタイトル
  fprintf(pipe,"set xlabel \"Classes\"\n");  // x軸のラベル
  fprintf(pipe,"set xrange [-0.05:1.05]\n");  // x軸の範囲
  fprintf(pipe,"set xtics 0.1\n");  // x軸メモリの間隔
  fprintf(pipe,"set ylabel \"Frequency /times\"\n");  // y軸のラベル
  fprintf(pipe,"set yrange [0:%f]\n",fmax*1.2);  // y軸の範囲（最大個数の２割増）
  fprintf(pipe,"set ytics %d\n",fstep);  // y軸メモリの間隔
  fprintf(pipe,"set size square\n");  // グラフの縦横比：正方形

  fprintf(pipe,"set boxwidth 0.95 relative\n");  // 棒グラフの幅
  fprintf(pipe,"plot \"12_frequency.dat\" with boxes\n");  // 棒グラフ表示
  fflush(pipe);

  fprintf(pipe,"set term png \n"); // 出力先をpngに変更
  fprintf(pipe,"set output \"12_frequency.png\"\n");  //pngファイル名
  fprintf(pipe,"replot \n");  // 再描画
  fflush(pipe);

  pclose(pipe);
}
