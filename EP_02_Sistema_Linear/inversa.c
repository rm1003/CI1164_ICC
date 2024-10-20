#include "includes.h"

int main () {
    ll n; scanf("%lld", &n);
    double tempo;

    PSISTEMA_LINEAR sistema = init_system(n);
    input(sistema);

    fesetround(FE_DOWNWARD);
    tempo = timestamp();
    solve(sistema);
    tempo = timestamp() - tempo;

    //printf("\n");
    output_inverse(sistema);

    //printf("\n");
    //output(sistema);
    free_SL(sistema);

    printf("%.8e\n", tempo);
    return 0;
}