#include "lu.h"

void identidade (PSISTEMA_LINEAR sistema) {
    for (int i = 0; i < sistema->ordem; ++i) {
        sistema->mIdentidade[i][i] = 1.0;
    }
    return;
}

void fat_LU (PSISTEMA_LINEAR sistema) {
    double m;
    ll n = sistema->ordem;
    identidade(sistema);
    for (int i = 0; i < n; ++i) {
        for (int k = i + 1; k < n; ++k) {
            m = sistema->matriz.mA[k][i] / sistema->matriz.mA[i][i];
            sistema->matriz.L[k][i] = m;
            for (int j = i + 1; j < n; ++j) {
                sistema->matriz.U[k][j] -= sistema->matriz.U[i][j] * m;
            }
        }
    }
    return;
}

void solve (PSISTEMA_LINEAR sistema) {
    ll n = sistema->ordem;
    fat_LU(sistema);
    // Resolve matriz LY = B
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            sistema->y[k][i] = sistema->mIdentidade[k][i];
            for (int j = 0; j < k; ++j) {
                sistema->y[k][i] -= sistema->matriz.L[k][j] * sistema->y[j][i];
            }
        }
        for (int k = n - 1; k >= 0; --k) {
            sistema->mAInversa[k][i] = sistema->y[k][i];
            for (int j = k + 1; j < n; ++j) {
                sistema->mAInversa[k][i] -= sistema->matriz.U[k][j] * sistema->mAInversa[j][i];
            }
            sistema->mAInversa[k][i] /= sistema->matriz.U[k][k];
        }
    }

    // Resolve matriz UX = Y
    // for (int i = 0; i < n; ++i) {
    //     for (int k = n - 1; k >= 0; --k) {
    //         sistema->mAInversa[k][i] = sistema->y[k][i];
    //         for (int j = k + 1; j < n; ++j) {
    //             sistema->mAInversa[k][i] -= sistema->matriz.U[k][j] * sistema->mAInversa[j][i];
    //         }
    //         sistema->mAInversa[k][i] /= sistema->matriz.U[k][k];
    //     }
    // }
    return;
}