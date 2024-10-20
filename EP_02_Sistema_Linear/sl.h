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
    }matriz;

    double **y; // Matriz auxiliar Y
    double **mAInversa; // Matriz Inversa de A
    double **mIdentidade; // Matriz Identidade
    double residuoL2; // Valor do residuo de norma L2
    ll ordem;
}sistema_linear;
typedef sistema_linear SISTEMA_LINEAR, *PSISTEMA_LINEAR;

// Coloca valor 0 em todas matrizes
void mem_set (PSISTEMA_LINEAR sistema);

// Inicializa o sistema linear
PSISTEMA_LINEAR init_system(ll ordem);

// Liberando memoria da estrutura inteira
void free_SL (PSISTEMA_LINEAR sistema);

#endif /* sl.h */