#include "io.h"

// Coloca os valores na matriz inicial A
void input (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        for (int j = 0; j < sistema->ordem; ++j) {
            scanf("%lf", &sistema->mA[i][j]);
        }
    }
    return;
}

// Imprime a ordem e os valores da matriz inversa de A
void output_inverse (PSISTEMA_LINEAR sistema) {
    printf("%lld\n", sistema->ordem);
    for (int i = 0; i < sistema->ordem; ++i) {
        for (int j = 0; j < sistema->ordem; ++j) {
            printf("%.15e ", sistema->mAInversa[i][j]);
        }
        printf("\n");
    }
    return;
}

// Para teste de se mem_set funciona ou nao
void output (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        for (int j = 0; j < sistema->ordem; ++j) {
            printf("%.15e ", sistema->mIdentidade[i][j]);
        }
        printf("\n");
    }
    return;
}