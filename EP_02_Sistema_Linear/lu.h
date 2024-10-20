#ifndef __LU_H__
#define __LU_H__

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "sl.h"

void identidade (PSISTEMA_LINEAR sistema);
void fat_LU (PSISTEMA_LINEAR sistema);
void solve (PSISTEMA_LINEAR sistema);


#endif /* lu.h */