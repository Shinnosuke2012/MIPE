// Monte-Carlo methods

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.141

int main(){
  int n,seed,i,c;
  double x,y,z,rr,v,pi;
  
  seed = time(NULL);  // 擬似乱数の種
  srand((unsigned int)seed);  // 擬似乱数の初期化

  printf("\nInput trial numbers!。\n  n= ");
  scanf("%d", &n);

  c = 0;  // 擬似乱数の点(x,y,z)が半径１の球内に入った回数cの初期化
  for(i=0 ; i<n ; i++){
    x = 2.*(PI/2.)*(double)rand()/RAND_MAX -(PI/2.); // -pi/2≦x≦pi/2の擬似乱数
    y = 2.*(double)rand()/RAND_MAX -1.; // -1≦y≦1の擬似乱数
    z = 2.*(double)rand()/RAND_MAX -1.; // -1≦z≦1の擬似乱数
    rr = y*y + z*z;
    if((sin(x)*sin(x) <= rr) && (rr<=1.)) c++;  // 擬似乱数の点(x,y,z)が半径sin(x)以上、半径１の球内に入った.
  }
  
  v = 4.*PI*(double)c/(double)n;  // 回転体の体積

  printf("\n Trial numbers: n = %d\n",n);
  printf(" Volume : v = %9.7f\n",v);

  exit(0);
}

