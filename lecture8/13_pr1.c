// 逐次比較法

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
  int i,j,k,min,Nmax,d[150];
  char id[150][9],line[21],temp[9];
  FILE *fp;

  printf("\n データを読み込みます．\n\n");
  fp=fopen("13_data.txt","r");  // データファイルを開く

  i=0;  // データ個数の初期化
  while(fgets(line,21,fp) != NULL){  // データが無くなったら繰返し終了
    sscanf(line,"%s %d",id[i],&d[i]);  // 読込んだ文字列から，学籍番号とデータ値を入力
    printf("%3d  %s  %5d\n",i+1,id[i],d[i]);
    i++;
  }
  fclose(fp);

  Nmax = i;  // データ個数
  printf("\n データの数は：Nmax = %d 個です．\n",Nmax);

  printf("\n 学籍番号をデータの値が小さい順に並べ替えます．\n");

  printf("\n Hit [return] key!\n");
  getchar();

  for(i=0 ; i<Nmax ; i++){
    min = d[i];
    strcpy(temp,id[i]);
    k = i;
    for(j=i+1 ; j<Nmax ; j++){
      if(d[j] < min){
        min = d[j];  // 一時的なデータの最小値
        strcpy(temp,id[j]);  // 一時的な最小値の学籍番号
        k = j;  //  一時的な最小値のデータ番号（配列添字）
      }
    }
    if(k != i){
      d[k] = d[i];
      d[i] = min;  // 最小値
      strcpy(id[k],id[i]);
      strcpy(id[i],temp);  // 最小値の学籍番号（文字列のコピー）
    }
  }

// 並べ替えた結果の出力
  printf("\n 並べ替えた結果を画面に出力します．\n");

  printf("\n Hit [return] key!\n");
  getchar();

  for(i=0 ; i<Nmax ; i++){ 
    printf("%3d  %5d  %s\n",i+1,d[i],id[i]);  // 文字列の表示には %s を用いる．
  }
  printf("\n");

  printf("\n 並べ替えた結果をファイル(13_data_sorted.txt)に出力します．\n");

  printf("\n Hit [return] key!\n");
  getchar();

  fp=fopen("13_data_sorted.txt","w");
  for(i=0 ; i<Nmax ; i++){ 
    fprintf(fp,"%3d  %5d  %s\n",i+1,d[i],id[i]);
  }
  fclose(fp);
}
