/* 06_pr1.c : 数値積分（シンプソンの公式）による1/4円の面積 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double func(double x){  // 関数の宣言：被積分関数（円）
  return sqrt(1.-x*x);
}

int main(){
  int n,i;
  double a,b,c,fa,fb,fc,s,h;

  printf("Input an even number, n=? ");  // nは偶数
  scanf("%d",&n);  // 積分区間の分割数
  
  printf("\nCalculating a quarter area of a circle.\n\n");

  h = 1./(double)n;  // 分割の幅
  a = 0.;  // 区間の左端
  fa = func(a);
  s = 0.;
  for(i=0;i<(n/2-1);i++){  // 一歩手前まで
      b = a + h;  //区間の右端
      fb = func(b);
      c = b + h;
      fc = func(c);
      s = s + (fa+4.*fb+fc)*h/3.; // シンプソンの公式
      a = c; //右端⇒左端に更新
      fa = fc;
  }
  c = 1.; // 最後は円の右端
  fc = func(c);
  b = (a+c)/2.;
  fb = func(b);
  s = s + (fa+4.*fb+fc)*h/3.; // シンプソンの公式

  printf("n= %d , s= %6.4f , pi= %10.8f \n",n,s,s*4.);

  exit(0);
}

