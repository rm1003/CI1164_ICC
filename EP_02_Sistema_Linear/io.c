/*
    Ruibin Mei
    GRR20232358

    io.c contem as funcoes para fazer leitura e saida de dados.
*/

#include "io.h"

// Faz leitura dos valores na matriz inicial A
void input (PSISTEMA_LINEAR sistema) {
    ll n = sistema->ordem;
    long double x;
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            scanf("%Lf", &x);
            sistema->matriz.mA[i][j] = x;
            sistema->mOriginal[i][j] = x;
        }
        sistema->mask[i] = i;
    }
    return;
}

// Imprime a ordem e os valores da matriz inversa de A
void output_inverse (PSISTEMA_LINEAR sistema) {
    printf("%lld\n", sistema->ordem);
    for (ll i = 0; i < sistema->ordem; ++i) {
        for (ll j = 0; j < sistema->ordem; ++j) {
            printf("%.15Le ", sistema->mAInversa[i][j]);
        }
        printf("\n");
    }
    return;
}

// Fucao para debug -> teste se mem_set funciona ou nao
void output (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        for (int j = 0; j < sistema->ordem; ++j) {
            printf("%Lf ", sistema->mIdentidade[i][j]);
        }
        printf("\n");
    }
    return;
}