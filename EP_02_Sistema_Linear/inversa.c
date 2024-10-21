/*
    Ruibin Mei
    GRR20232358

    Funcao main onde apenas faz chamada das funcoes.
*/

#include "includes.h"

int main () {
    // Leitura de entrada
    ll n; scanf("%lld", &n);
    if (n == 0) {
        perror("Entrada menor que 1\n");
        return 0;
    }
    PSISTEMA_LINEAR sistema = init_system(n);
    input(sistema);

    LIKWID_MARKER_INIT;
    printf("/inicio\n");
    LIKWID_MARKER_START("marker");

    fesetround(FE_DOWNWARD);
    solve(sistema);

    LIKWID_MARKER_STOP("marker");
    LIKWID_MARKER_CLOSE;

    residuo(sistema);

    output_inverse(sistema);

    printf("%.15Le\n", sistema->residuoL2);
    printf("%.8Le\n", sistema->tempo);
    free_SL(sistema);
    printf("/fim\n");
    return 0;
}