/*
    Ruibin Mei
    GRR20232358

    Biblioteca com as funcoes para sistema linear, ou seja,
    todas as matrizes sao definidas nessa biblioteca.
*/

#ifndef __SL_H__
#define __SL_H__

#include <stdlib.h>
#include <string.h>
#include "defines.h"

typedef struct {
    // Matriz LU tudo junto para gastar menos memoria
    union {
        double **mA;
        double **U;
        double **L;
    } matriz;

    double **mOriginal; // Matriz original para fazer calculo do residuo

    double **y; // Matriz auxiliar Y no calculo de UX = Y
    double **mAInversa; // Matriz Inversa de A
    double **mIdentidade; // Matriz Identidade

    ll *mask; // Vetor auxiliar para ordem das linhas no pivoteamento

    double tempo; // Variavel para guardar o tempo no calculo da inversa
    double residuoL2; // Valor do residuo de norma L2
    ll ordem; // Ordem da matriz
}sistema_linear;
typedef sistema_linear SISTEMA_LINEAR, *PSISTEMA_LINEAR;

// Coloca valor 0 em todas matrizes
void mem_set (PSISTEMA_LINEAR sistema);

// Inicializa todas as matrizes 
PSISTEMA_LINEAR init_system(ll ordem);

// Liberando memoria da estrutura inteira
void free_SL (PSISTEMA_LINEAR sistema);

#endif /* sl.h */