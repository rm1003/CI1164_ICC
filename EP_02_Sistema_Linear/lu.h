/*
    Ruibin Mei
    GRR20232358

    Biblioteca com as funcoes para fazer o calculo da matriz 
    inversa pelo metodo da fatoracao LU com pivoteamento parcial.
*/

#ifndef __LU_H__
#define __LU_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "defines.h"
#include "sl.h"

// Faz a troca das linhas da matriz inversa
void swap_inverse (PSISTEMA_LINEAR sistema, ll a, ll b);

// Ordena a matriz inversa
void ordena_matriz (PSISTEMA_LINEAR sistema);

// Troca das linhas
void swap (PSISTEMA_LINEAR sistema, int a, int b);

// Acha o maior valor para pivoteamento e faz a troca das linhas
void max_swap (PSISTEMA_LINEAR sistema, int atual);

// Gera a matriz identidade
void init_identidade (PSISTEMA_LINEAR sistema);

// Gera as matrizes LU
void fat_LU (PSISTEMA_LINEAR sistema);

// Resolve a matriz inversa usando o Método da Fatoração LU com pivoteamento parcial
void solve (PSISTEMA_LINEAR sistema);

// Calcula o residuo de norma L2
void residuo (PSISTEMA_LINEAR sistema);

#endif /* lu.h */