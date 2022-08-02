#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//まず乱数を生成し、そのあとに乱数を発生回数によりソートする。
int main(){
  int n,a,b,seed,s[10],f[10],c;
  int fstep,fmax,prn;
  FILE *fp;
  
  for(a=0 ; a<10 ; a++) f[a]=0; // 擬似乱数の個数を数える配列の初期化
    
  seed = time(NULL); // 擬似乱数の種
  srand((unsigned int)seed); // 擬似乱数の初期化

  printf("\n RAND_MAX= %d\n",RAND_MAX); // RAND_MAX値の確認（2,147,483,647）

  printf("\n 作成する擬似乱数の個数：n(10以下) を入力して下さい。\n");
  printf("   n= ");
  scanf("%d", &n);
  
  for(b=0 ; b<n ; b++){ // 擬似乱数(-25.≦prn＜25.)の作成
    prn =  (int)((2.*25 +1.)*rand() / (RAND_MAX+1.)) - 25;
    s[b] = prn;
    c = (int)((prn + 25)*(9./50.));  // 擬似乱数の値(-25≦prn≦25)を配列の添字（0≦i≦9）に変換
    f[c]++; // 乱数の発生個数分布を調べるための配列
  }

  fmax = 0; // 乱数の発生個数の最大値の初期化
  printf("\n seed = %d\n\n",seed);  // 乱数の種値を表示
  
  for(a=0 ; a<10 ; a++){ // 擬似乱数の分布(-25から25までを5刻みで表示する)
    printf(" %d / f[%d]=%d\n",s[a],a,f[a]); // 画面出力
  }

  //ここまでが乱数生成のプログラムである。
  //ここからソートプログラムをつくる。

  int i,j,k,max,Nmax,temp;

  Nmax = n;  // データ個数
  printf("\n データの数は：Nmax = %d 個です．\n",Nmax);

  printf("\n 発生させた乱数を発生回数の大きい順に並べ替えます．\n");

  for(i=0 ; i<Nmax ; i++){
    max = f[i];
    temp= s[i];
    k = i;
    for(j=i+1 ; j<Nmax ; j++){
      if(f[j] > max){
        max = f[j];  // 一時的な発生回数の最小値
        temp=s[j];  // 一時的な最小値の乱数
        k = j;  //  一時的な最小値の配列添字
      }
    }
    if(k != i){
      f[k] = f[i];
      f[i] = max;  // 最小値
      s[k] = s[i];
      s[i]= temp;  // 最小値の乱数
    }
  }

// 並べ替えた結果の出力
  printf("\n 並べ替えた結果を画面に出力します．\n");
  printf("順位: 乱数の値: 発生回数 を表している. \n");

  for(i=0 ; i<Nmax ; i++){ 
    printf("%d  %d  %d\n",i+1,s[i],f[i]);
  }
  printf("\n");

  printf("\n 並べ替えた結果をファイル(C0TB1060-8.txt)に出力します．\n");

  fp=fopen("C0TB1060-8.txt","w");
  for(i=0 ; i<Nmax ; i++){ 
    fprintf(fp,"%d  %d  %d\n",i+1,s[i],f[i]);
  }
  fclose(fp);
}