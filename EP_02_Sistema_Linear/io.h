#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "sl.h"

// Coloca os valores na matriz inicial A
void input (PSISTEMA_LINEAR sistema);

// Imprime a ordem e os valores da matriz inversa de A
void output_inverse (PSISTEMA_LINEAR sistema);

// Para teste de se mem_set funciona ou nao
void output (PSISTEMA_LINEAR sistema);

#endif /* io.h */