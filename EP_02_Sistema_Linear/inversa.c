/*
    Ruibin Mei
    GRR20232358

    Funcao main onde apenas faz chamada das funcoes.
*/

#include "includes.h"

int main () {
    LIKWID_MARKER_INIT;

    // Leitura de entrada
    ll n; scanf("%lld", &n);
    if (n == 0) {
        perror("Entrada menor que 1\n");
        return 0;
    }
    PSISTEMA_LINEAR sistema = init_system(n);
    input(sistema);

    printf("/marcacao-inicial\n");

    LIKWID_MARKER_START("marker");

    fesetround(FE_DOWNWARD);
    solve(sistema);

    LIKWID_MARKER_STOP("marker");

    residuo(sistema);

    output_inverse(sistema);

    printf("%.15e\n", sistema->residuoL2);
    printf("%.8e\n", sistema->tempo);

    printf("/marcacao-final\n");

    free_SL(sistema);
    LIKWID_MARKER_CLOSE;
    return 0;
}