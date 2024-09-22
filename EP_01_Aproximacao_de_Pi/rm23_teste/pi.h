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

#define CASA_D 15

#define ABS(a, b) ((a > b) ? a - b : b - a)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef union{
    double value;
    uint32_t hexa;
} DOUBLE_HEXA;

void arredondar (double valor, int casas_decimais);

double somatoria (double tolerancia);

void aproxima_pi (double tolerancia);


#endif /* pi.h */