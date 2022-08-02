//By using the algorithm of dinary seeking, finding the solution of exp(x) - x^2 = 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1.0E-6 //threshfold of convergence
#define samesign(x,y) (x*y > 0)
#define oppositesign(x,y) (x*y < 0)

//define the function of exp(x) - x^2
double function(double x){
    return exp(x) - x*x;
}

//judging the condition
int main(){
    int n,i,ni;
    double a0,b0,a,b,c,fa,fb,fc;

    printf("Maximum iteration : n \n");
    printf("n = "); scanf("%d",&n);
    printf("input initial a and b which satisfies a0<b0 ! \n");
    printf("a0 = "); scanf("%lf",&a0);
    printf("b0 = "); scanf("%lf",&b0);

    if (a0 > b0){
        c = a0; a0=b0; b0=c; //swapping a0 and b0
    }

    fa = function(a0);
    fb = function(b0);

    if (samesign(fa,fb)){
        printf("In both sides, the sign is the same \n");
    }

    else {
        printf("In both sides, the sign is opposie \n");
    }

    //loop until solution is found
    a = a0; 
    b = b0;
    i = 1;

    do{
        c = (a + b)/2;
        fc = function(c);
        if (samesign(fa,fc)){
            a = c;
            fa = fc;
            // if fa and fc are the same sign, update c as new a
        }
        else if (oppositesign(fa,fc)) {
            b = c;
            fb = fc;
            //otherwise, update c as new b
        }
        ni = i;
        i = i + 1;
    } while((n>i) && (EPS < fabs(c)));

    printf("Result \n");
    printf("Initial: [a,b] = [%f,%f]\n", a0,b0);
    printf("Number of loop = %d \n",ni);
    printf("Solution x = %f \n",c);

    exit(0);
}