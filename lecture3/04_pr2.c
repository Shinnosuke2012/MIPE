/* 04_pr2.c : 数値積分（台形公式）による1/4円の面積 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double func(double x){  // 関数の宣言：被積分関数（円）
  return sqrt(1.-x*x);
}

int main(){
  int n,i;
  double a,b,fa,fb,s,h;

  printf("Input n=? ");
  scanf("%d",&n);  // 積分区間の分割数
  
  printf("\nCalculating a quarter area of a circle.\n\n");

  h = 1./(double)n;  // 台形の高さ
  a = 0.;  // 台形の左端
  fa = func(a);  // 台形の底辺
  s = 0.;
  for(i=0;i<(n-1);i++){  // 一歩手前まで
      b = a + h;  // 台形の右端
      fb = func(b);  // 台形の上底
      s = s + (fb+fa)*h/2.; // 台形の面積の積算
      a = b;  //右端⇒左端
      fa = fb;
  }
  b = 1.;  // 最後は円の右端
  fb = func(b);
  s = s + (fb+fa)*(b-a)/2.;  // 台形の面積の積算

  printf("n= %d , s= %6.4f , pi= %10.8f \n",n,s,s*4.);  // 計算結果の出力（画面）

  exit(0);
}
