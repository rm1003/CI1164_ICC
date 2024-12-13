#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <fenv.h>
#include <math.h>
#include <stdint.h>
#include <likwid.h>
#include "utils.h"

#define UNROLL_LINES 4
#define BLOCKING 64
/////////////////////////////////////////////////////////////////////////////////////
//   AJUSTE DE CURVAS
/////////////////////////////////////////////////////////////////////////////////////

// OK
// Add restrict para poder distinguir as matrizes
void montaSL(double **restrict A, double *restrict b, int n, long long int p, double *restrict x, double *restrict y)
{
    // Antecipa calculo do pow para reutilização em vez de calcular novamente toda vez
    // max_power = para valor max da quantidade de somatorias do SL
    long long int max_power = 2 * n - 1;
    double vpow = 0.0;
    double *powers = (double *)malloc((max_power) * sizeof(double));
    for (long long int i = 0; i < n; ++i)
    {
        b[i] = 0.0;
        powers[i] = 0.0;
        for (long long int j = 0; j < p; ++j)
        {
            vpow = pow(x[j], i);
            powers[i] += vpow;
            b[i] += vpow * y[j];
        }
    }
    for (long long int i = n; i < max_power; ++i)
    {
        powers[i] = 0.0;
        for (long long int j = 0; j < p; ++j)
        {
            powers[i] += pow(x[j], i);
        }
    }

    for (long long int i = 0; i < n; ++i)
        for (long long int j = 0; j < n; ++j)
            A[i][j] = powers[i + j];
}

void eliminacaoGauss(double **restrict A, double *restrict b, int n)
{
    for (long long int i = 0; i < n; ++i)
    {
        long long int iMax = i;
        for (long long int k = i + 1; k < n; ++k)
        {
            if (A[k][i] > A[iMax][i])
                iMax = k;
        }
        if (iMax != i)
        {
            double *tmp = A[i];
            A[i] = A[iMax];
            A[iMax] = tmp;

            double aux = b[i];
            b[i] = b[iMax];
            b[iMax] = aux;
        }

        for (long long int k = i + 1; k < n; ++k)
        {
            double m = A[k][i] / A[i][i];
            A[k][i] = 0.0;
            for (int j = i + 1; j < n; ++j)
                A[k][j] -= A[i][j] * m;
            b[k] -= b[i] * m;
        }
        
    }
}

void retrossubs(double **restrict A, double *restrict b, double *restrict x, int n)
{
    for (long long int i = n - 1; i >= 0; --i)
    {
        double soma = 0.0;
        long long int j;

        // Unroll com blocos menores que respeitam a dependência de dados
        for (j = i + 1; j + 3 < n; j += UNROLL_LINES) // Processa 4 elementos por iteração
        {
            soma += A[i][j] * x[j] +
                    A[i][j + 1] * x[j + 1] +
                    A[i][j + 2] * x[j + 2] +
                    A[i][j + 3] * x[j + 3];
        }
        // Calcula os elementos restantes
        for (; j < n; ++j)
        {
            soma += A[i][j] * x[j];
        }
        // for (long long int j = i + 1; j < n; ++j)
        // {
        //     soma += A[i][j] * x[j];
        // }
        x[i] = (b[i] - soma) / A[i][i];
    }
}

double P(double x, int N, double *alpha)
{
    double Px = alpha[0];
    for (int i = 1; i <= N; ++i)
        Px += alpha[i] * pow(x, i);

    return Px;
}

int main()
{

    int N, n;
    long long int K, p;

    scanf("%d %lld", &N, &K);
    p = K;     // quantidade de pontos
    n = N + 1; // tamanho do SL (grau N + 1)

    double *x = (double *)malloc(sizeof(double) * p);
    double *y = (double *)malloc(sizeof(double) * p);

    // ler numeros
    for (long long int i = 0; i < p; ++i)
        scanf("%lf %lf", x + i, y + i);

    double **A = (double **)malloc(sizeof(double *) * n);
    for (int i = 0; i < n; ++i)
        A[i] = (double *)malloc(sizeof(double) * n);

    double *b = (double *)malloc(sizeof(double) * n);
    double *alpha = (double *)malloc(sizeof(double) * n); // coeficientes ajuste

    LIKWID_MARKER_INIT;
    LIKWID_MARKER_START("montaSL");

    // (A) Gera SL
    double tSL = timestamp();
    montaSL(A, b, n, p, x, y);
    tSL = timestamp() - tSL;

    LIKWID_MARKER_STOP("montaSL");

    LIKWID_MARKER_START("resolveSL");

    // (B) Resolve SL
    double tEG = timestamp();
    eliminacaoGauss(A, b, n);
    retrossubs(A, b, alpha, n);
    tEG = timestamp() - tEG;

    LIKWID_MARKER_STOP("resolveSL");

    LIKWID_MARKER_CLOSE;

    // Imprime coeficientes
    for (int i = 0; i < n; ++i)
        printf("%1.15e ", alpha[i]);
    puts("");

    // Imprime resíduos
    for (long long int i = 0; i < p; ++i)
        printf("%1.15e ", fabs(y[i] - P(x[i], N, alpha)));
    puts("");

    // Imprime os tempos
    printf("%lld %1.10e %1.10e\n", K, tSL, tEG);

    return 0;
}
