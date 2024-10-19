#include "sl.h"

// Coloca valor 0 em todas matrizes
void mem_set (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        memset(sistema->mA[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->mAInversa[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->mIdentidade[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->U[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->L[i], 0.0, sistema->ordem * sizeof(double));
    }
    return;
}

PSISTEMA_LINEAR init_system(ll ordem) {
    PSISTEMA_LINEAR aux = malloc(sizeof(*aux));

    aux->ordem = ordem;

    aux->mA = malloc(ordem * sizeof * aux->mA);
    aux->mAInversa = malloc(ordem * sizeof * aux->mAInversa);
    aux->U = malloc(ordem * sizeof * aux->U);
    aux->L = malloc(ordem * sizeof * aux->L);
    aux->mIdentidade = malloc(ordem * sizeof * aux->mIdentidade); 
    for (int i = 0; i < ordem; ++i) {
        aux->mA[i] = malloc(ordem * sizeof **aux->mA);
        aux->mAInversa[i] = malloc(ordem * sizeof **aux->mAInversa);
        aux->U[i] = malloc(ordem * sizeof ** aux->U);
        aux->L[i] = malloc(ordem * sizeof ** aux->L);
        aux->mIdentidade[i] = malloc(ordem * sizeof ** aux->mIdentidade); 
    }
    mem_set(aux);
    return aux;
}

void free_SL (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        free(sistema->mA[i]);
        free(sistema->mAInversa[i]);
        free(sistema->mIdentidade[i]);
        free(sistema->L[i]);
        free(sistema->U[i]);
    }
    free(sistema->mA);
    free(sistema->mAInversa);
    free(sistema->mIdentidade);
    free(sistema->L);
    free(sistema->U);
    free(sistema);
    return;
}