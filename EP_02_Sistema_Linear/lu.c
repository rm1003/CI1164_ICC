/*
    Ruibin Mei
    GRR20232358

    lu.c sao todas as funcoes para fazer o calculo da matriz 
    inversa pelo metodo da fatoracao LU com pivoteamento parcial.
*/

#include "lu.h"

// Faz a troca das linhas da matriz inversa
void swap_inverse (PSISTEMA_LINEAR sistema, ll a, ll b) {
    long double *aux;
    // Inverte a matriz inversa para posicao correta
    aux = sistema->mAInversa[a];
    sistema->mAInversa[a] = sistema->mAInversa[b];
    sistema->mAInversa[b] = aux;
    // Inverte a matriz identidade
    aux = sistema->mIdentidade[a];
    sistema->mIdentidade[a] = sistema->mIdentidade[b];
    sistema->mIdentidade[b] = aux;
    return;
}

// Ordena a matriz inversa atraves da mascara - Insertion Sort
void ordena_matriz (PSISTEMA_LINEAR sistema) {
    ll key, j, aux;
    for (ll i = 1; i < sistema->ordem; ++i) {
        key = sistema->mask[i];
        j = i - 1;

        while (j >= 0 && sistema->mask[j] > key) {
            sistema->mask[j + 1] = sistema->mask[j];
            swap_inverse(sistema, j+1, j);
            j -= 1;
        }
        sistema->mask[j + 1] = key;
    }
    return;
}

// Troca das linhas da matriz principál e identidade 
void swap (PSISTEMA_LINEAR sistema, int a, int b) {
    long double *aux;
    ll tmp;
    // Troca das linhas da matriz original
    aux = sistema->matriz.mA[a];
    sistema->matriz.mA[a] = sistema->matriz.mA[b];
    sistema->matriz.mA[b] = aux;
    // Troca das linhas da matriz identidade
    aux = sistema->mIdentidade[a];
    sistema->mIdentidade[a] = sistema->mIdentidade[b];
    sistema->mIdentidade[b] = aux;
    // Troca o valor no vetor de mascara das linhas corretas
    tmp = sistema->mask[a];
    sistema->mask[a] = sistema->mask[b];
    sistema->mask[b] = tmp;
    return;
}

// Acha o maior valor para pivoteamento e faz a troca das linhas
void max_swap (PSISTEMA_LINEAR sistema, int atual) {
    long double maior = fabs(sistema->matriz.mA[atual][atual]);
    ll i, i_maior = atual;
    // Acha o maior valor para pivoteamento parcial
    for (i = atual + 1; i < sistema->ordem; ++i) {
        if (maior < fabs(sistema->matriz.mA[i][atual])) {
            i_maior = i;
            maior = fabs(sistema->matriz.mA[i][atual]);
        }
    }
    // Se for diferente da linha atual, faz a troca
    if (atual != i_maior) {
        swap(sistema, atual, i_maior);
    }
    return;
}

// Gera a matriz identidade
void init_identidade (PSISTEMA_LINEAR sistema) {
    for (ll i = 0; i < sistema->ordem; ++i) {
        sistema->mIdentidade[i][i] = 1.0;
    }
    return;
}

// Gera as matrizes LU
void fat_LU (PSISTEMA_LINEAR sistema) {
    long double m;
    ll n = sistema->ordem;
    init_identidade(sistema);
    for (ll i = 0; i < n; ++i) {
        // Pivoteamente parcial
        max_swap(sistema, i);
        // Aqui faz eliminacao de Gauss
        for (ll k = i + 1; k < n; ++k) {
            // Considerando que o caso de divisao por 0 devolva 0.0
            if (sistema->matriz.mA[i][i] != 0) {
                m = sistema->matriz.mA[k][i] / sistema->matriz.mA[i][i];
            } else {
                m = 0.0;
            }
            sistema->matriz.L[k][i] = m;
            for (ll j = i + 1; j < n; ++j) {
                sistema->matriz.U[k][j] -= sistema->matriz.U[i][j] * m;
            }
        }
    }
    return;
}

// Resolve a matriz inversa usando o Método da Fatoração LU com pivoteamento parcial
void solve (PSISTEMA_LINEAR sistema) {
    ll n = sistema->ordem;
    sistema->tempo = timestamp();

    fat_LU(sistema);
    // Acha matriz inversa
    for (ll i = 0; i < n; ++i) {
        // Resolve matriz LY = B 
        for (ll k = 0; k < n; ++k) {
            sistema->y[k][i] = sistema->mIdentidade[k][i];
            for (ll j = 0; j < k; ++j) {
                sistema->y[k][i] -= sistema->matriz.L[k][j] * sistema->y[j][i];
            }
        }
        // Resolve matriz UX = Y
        for (ll k = n - 1; k >= 0; --k) {
            // Resolve a matriz
            sistema->mAInversa[k][i] = sistema->y[k][i];
            for (ll j = k + 1; j < n; ++j) {
                sistema->mAInversa[k][i] -= sistema->matriz.U[k][j] * sistema->mAInversa[j][i];
            }
            // Considerando que o caso de divisao por 0 devolva 0.0
            if (sistema->matriz.U[k][k] != 0) {
                sistema->mAInversa[k][i] /= sistema->matriz.U[k][k];
            } else {
                sistema->mAInversa[k][i] = 0.0;
            }
        }
    }
    sistema->tempo = timestamp() - sistema->tempo;
    ordena_matriz(sistema);
    return;
}

// Calcula o residuo de norma L2
void residuo (PSISTEMA_LINEAR sistema) {
    long double r_atual = 0.0, r_quadrado, r_final = 0.0, soma;

    ll n = sistema->ordem;
    // R = A.AI - I
    // Faz a multipĺicacao de matriz
    for (ll i = 0; i < n; ++i) {
        r_quadrado = 0.0;
        for (ll k = 0; k < n; ++k) {
            soma = 0.0; 
            // Aqui faz o calculo da matriz em coluna por coluna
            for (ll j = 0; j < n; ++j) {
                soma += sistema->mOriginal[k][j] * sistema->mAInversa[j][i];
            }
            // Calcula o valor atual do residuo e depois o quadrado
            r_atual = soma - sistema->mIdentidade[i][k];
            r_quadrado += r_atual * r_atual;
        }
        // Calcula a soma das raizes da soma dos quadrados dos residuos
        r_final += sqrt(r_quadrado);
    }
    // Calcula a media simples do residuo final
    sistema->residuoL2 = r_final / n;
    return;
}