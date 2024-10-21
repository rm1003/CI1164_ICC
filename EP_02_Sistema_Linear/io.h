/*
    Ruibin Mei
    GRR20232358

    Biblioteca com as funcoes para entrada e saida de dados.
*/

#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "sl.h"

// Faz leitura dos valores na matriz inicial A
void input (PSISTEMA_LINEAR sistema);

// Imprime a ordem e os valores da matriz inversa de A
void output_inverse (PSISTEMA_LINEAR sistema);

// Fucao para debug -> teste se mem_set funciona ou nao
void output (PSISTEMA_LINEAR sistema);

#endif /* io.h */