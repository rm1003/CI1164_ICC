/*
    Ruibin Mei
    GRR20232358

    sl.c possui todas as funcoes da biblioteca sl, na qual
    faz alocamento de memoria para as matrizes e colocar 
    valor 0.0 em todas as matrizes.
*/

#include "sl.h"

// Coloca valor 0.0 em todas matrizes
void mem_set (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        memset(sistema->matriz.mA[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->mOriginal[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->y[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->mAInversa[i], 0.0, sistema->ordem * sizeof(double));
        memset(sistema->mIdentidade[i], 0.0, sistema->ordem * sizeof(double));
    }
    return;
}

// Aloca a estrutura e todas matrizes que são usados para o resto do programa
PSISTEMA_LINEAR init_system(ll ordem) {
    PSISTEMA_LINEAR aux = malloc(sizeof(*aux));

    aux->ordem = ordem;

    // Alocacao de memoria
    aux->matriz.mA = malloc(ordem * sizeof * aux->matriz.mA);
    aux->mOriginal = malloc(ordem * sizeof * aux->mOriginal);
    aux->mask = malloc(ordem * sizeof * aux->mask);
    aux->y = malloc(ordem * sizeof * aux->y);
    aux->mAInversa = malloc(ordem * sizeof * aux->mAInversa);
    aux->mIdentidade = malloc(ordem * sizeof * aux->mIdentidade); 
    for (ll i = 0; i < ordem; ++i) {
        aux->matriz.mA[i] = malloc(ordem * sizeof ** aux->matriz.mA);
        aux->mOriginal[i] = malloc(ordem * sizeof ** aux->mOriginal);
        aux->y[i] = malloc(ordem * sizeof ** aux->y);
        aux->mAInversa[i] = malloc(ordem * sizeof ** aux->mAInversa);
        aux->mIdentidade[i] = malloc(ordem * sizeof ** aux->mIdentidade); 
    }
    mem_set(aux);
    return aux;
}

// Libera memoria de toda a estrutura e todas as matrizes
void free_SL (PSISTEMA_LINEAR sistema) {
    for (ll i = 0; i < sistema->ordem; ++i) {
        free(sistema->matriz.mA[i]);
        free(sistema->mOriginal[i]);
        free(sistema->y[i]);
        free(sistema->mAInversa[i]);
        free(sistema->mIdentidade[i]);
    }
    free(sistema->matriz.mA);
    free(sistema->mOriginal);
    free(sistema->mask);
    free(sistema->y);
    free(sistema->mAInversa);
    free(sistema->mIdentidade);
    free(sistema);
    return;
}