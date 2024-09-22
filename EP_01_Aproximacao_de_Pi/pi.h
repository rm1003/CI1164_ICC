#ifndef _PI_
#define _PI_

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <fenv.h>
#include <stdint.h>

#define ll long long
#define ull unsigned long long
#define ldouble long double

// #define CASA_D 15

#define ABS(a, b) ((a > b) ? a - b : b - a)

#define M_PI 3.14159265358979323846

typedef union{
    double value;
    int64_t hexa;
} DOUBLE_HEXA;

void arredondar (double valor);

double somatoria (double tolerancia, ll *count);

void aproxima_pi (double tolerancia);


#endif /* pi.h */