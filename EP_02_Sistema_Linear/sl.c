#include "sl.h"

// Coloca valor 0 em todas matrizes
void mem_set (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        memset(sistema->matriz.mA[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->y[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->mAInversa[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->mIdentidade[i], 0.0, sistema->ordem * sizeof(double));
    }
    return;
}

PSISTEMA_LINEAR init_system(ll ordem) {
    PSISTEMA_LINEAR aux = malloc(sizeof(*aux));

    aux->ordem = ordem;

    aux->matriz.mA = malloc(ordem * sizeof * aux->matriz.mA);
    aux->y = malloc(ordem * sizeof * aux->y);
    aux->mAInversa = malloc(ordem * sizeof * aux->mAInversa);
    aux->mIdentidade = malloc(ordem * sizeof * aux->mIdentidade); 
    for (int i = 0; i < ordem; ++i) {
        aux->matriz.mA[i] = malloc(ordem * sizeof ** aux->matriz.mA);
        aux->y[i] = malloc(ordem * sizeof ** aux->y);
        aux->mAInversa[i] = malloc(ordem * sizeof ** aux->mAInversa);
        aux->mIdentidade[i] = malloc(ordem * sizeof ** aux->mIdentidade); 
    }
    mem_set(aux);
    return aux;
}

void free_SL (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        free(sistema->matriz.mA[i]);
        free(sistema->y[i]);
        free(sistema->mAInversa[i]);
        free(sistema->mIdentidade[i]);
    }
    free(sistema->matriz.mA);
    free(sistema->y);
    free(sistema->mAInversa);
    free(sistema->mIdentidade);
    free(sistema);
    return;
}