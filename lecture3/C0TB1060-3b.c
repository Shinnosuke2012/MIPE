#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define R 8.31447
#define QD 428 // Debye temperature of Al
#define EPS 1.E-6

double func(double x)
{ // 関数の宣言：被積分関数
    return x * x * x * x * exp(x) / ((exp(x) - 1.) * (exp(x) - 1.));
}

int main()
{
    int n, i;
    double t, xmax, cv, a, b, fa, fb, s, h;

    printf("Calculating specific heat, Cv, of Be.\n");
    printf("T = ");
    scanf("%lf\n",&t); // Temperature, t/K
    xmax = QD / t; // max value of x
    n = 1000;      //number of boundaries
    h = xmax / (double)n;
    a = 0.;             //left side
    fa = func(a + EPS); // preventing crashing
    s = 0.;
    for (i = 0; i < (n - 1); i++)
    { //
        b = a + h;
        fb = func(b);
        s = s + (fa + fb) * h / 2.; // area of trepezoid
        a = b;                      
        fa = fb;
    }
    b = xmax; // right side of integration
    fb = func(b);
    s = s + (fa + fb) * (b - a) / 2.;                 // calculationg of area
    cv = 9. * R * (t / QD) * (t / QD) * (t / QD) * s; //specific heat
    printf("T= %6.1f , Cv= %8.4f \n", t, cv);

    exit(0);
}