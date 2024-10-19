#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include <math.h>

#define max(a, b) (a < b ? b : a)

typedef struct {
    double **mA, *mB, *ans;
    int ordem;
}sistema_linear;
typedef sistema_linear SISTEMA_LINEAR, *PSISTEMA_LINEAR;

PSISTEMA_LINEAR init_system(int ordem) {
    PSISTEMA_LINEAR aux = malloc(sizeof(*aux));

    aux->ordem = ordem;

    aux->mA = malloc(ordem * sizeof * aux->mA);
    for (int i = 0; i < ordem; ++i) {
        aux->mA[i] = malloc(ordem * sizeof **aux->mA);
    }
    aux->mB = malloc(ordem * sizeof * aux->mB);
    aux->ans = malloc(ordem * sizeof * aux->ans);

    return aux;
}

void res_sis_triangular(PSISTEMA_LINEAR sistema) {
    int ordem = sistema->ordem;
    for (int i = ordem - 1; i >= 0; --i) {
        sistema->ans[i] = sistema->mB[i];
        for (int j = i + 1; j < ordem; ++j) {
            sistema->ans[i] -= sistema->mA[i][j] * sistema->ans[j];
        }
        if (sistema->mA[i][i] != 0) {
            sistema->ans[i] /= sistema->mA[i][i];
        } else {
            if (sistema->ans[i] == 0) {
                printf("Sistema indeterminado\n");
            } else {
                printf("Sistema nao possivel\n");
            }
            return;
        }
    }
    return;
}

void eliminacaoGauss (PSISTEMA_LINEAR sistema) {
    int n = sistema->ordem;
    for (int i = 0; i < n; ++i) {
        for (int k = i + 1; k < n; ++k) {
            double m = sistema->mA[k][i] / sistema->mA[i][i];
            sistema->mA[k][i] = 0.0;
            for (int j = i + 1; j < n; ++j) {
                sistema->mA[k][j] -= sistema->mA[i][j] * m;
            }
            sistema->mB[k] -= sistema->mB[i] * m;
        }   
    }
    res_sis_triangular(sistema);
    return;
}

void swap (PSISTEMA_LINEAR sistema, int a, int b) {
    double *aux, tmp;
    aux = sistema->mA[a];
    sistema->mA[a] = sistema->mA[b];
    sistema->mA[b] = aux;
    tmp = sistema->mB[a];
    sistema->mB[a] = sistema->mB[b];
    sistema->mB[b] = tmp;
    return;
}

void max_swap (PSISTEMA_LINEAR sistema, int atual) {
    double maior = sistema->mA[atual][atual];
    int i, i_maior = atual;
    for (i = atual+1; i < sistema->ordem; ++i) {
        if (maior < fabs(sistema->mA[i][atual])) {
            i_maior = i;
            maior = fabs(sistema->mA[i][atual]);
        }
    }
    if (atual != i_maior) {
        swap(sistema, atual, i_maior);
    }
    return;
}

void eliminacaoGaussPP (PSISTEMA_LINEAR sistema) {
    int n = sistema->ordem;
    for (int i = 0; i < n; ++i) {
        max_swap(sistema, i);
        for (int k = i + 1; k < n; ++k) {
            double m = sistema->mA[k][i] / sistema->mA[i][i];
            sistema->mA[k][i] = 0.0;
            for (int j = i + 1; j < n; ++j) {
                sistema->mA[k][j] -= sistema->mA[i][j] * m;
            }
            sistema->mB[k] -= sistema->mB[i] * m;
        }   
    }
    res_sis_triangular(sistema);
    return;
}

void input (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        for (int j = 0; j < sistema->ordem; ++j) {
            scanf("%lf", &sistema->mA[i][j]);
        }
        scanf("%lf", &sistema->mB[i]);
    }

    return;
}

void output_ans (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        printf("%lf ", sistema->ans[i]);
    }
    printf("\n");
    return;
}

void output (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        for (int j = 0; j < sistema->ordem; ++j) {
            printf("%lf ", sistema->mA[i][j]);
        }
        printf("%lf\n", sistema->mB[i]);
    }
    return;
}

void free_SL (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        free(sistema->mA[i]);
    }
    free(sistema->mA);
    free(sistema->mB);
    free(sistema->ans);
    free(sistema);
    return;
}

int main () {
    int ordem; scanf("%d", &ordem);
    
    fesetround(FE_DOWNWARD);
    PSISTEMA_LINEAR sistema = init_system(ordem);
    input(sistema);
    eliminacaoGaussPP(sistema);

    output_ans(sistema);

    free_SL(sistema);

    return 0;
}
