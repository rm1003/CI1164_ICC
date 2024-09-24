#include "pi.h"


double somatoria (double tolerancia, ll *count, int mode) {
    ll it = 0;
    
    double pow_2k = 1; // 2^k
    double fat_k = 1; // k!
    double fat_Denominador = 1; // (2k + 1)!
    double sum = 0.0;
    double termo, pi_anterior, diff;

    DOUBLE_HEXA diference, pi;

    do {
        termo = ((pow_2k*fat_k*fat_k) / fat_Denominador); // 3 operacoes
        pi_anterior = sum;
        sum += termo; // 1 operacao
        it++;
        fat_k *= it; // 1 operacao
        pow_2k *= 2; // 1 operacao
        fat_Denominador *= ((2*it) * ((2*it) + 1)); // 5 operacoes
        diff = fabs(sum - pi_anterior)*2; // 3 operacoes
        (*count) += 10;
        // total 14 operacoes dentro do loop
    } while (diff >= tolerancia);
    
    if (mode != 0) {
        // Erros
        diference.value = diff;
        pi.value = fabs((sum*2) - M_PI); // 3 operacoes
        printf("%lld\n", it);
        printf("%.15e %lX\n", diference.value, diference.hexa);
        printf("%.15e %lX\n", fabs((sum*2) - M_PI), pi.hexa); // 3 operacoes
        (*count) += 6; // dentro do if sao 6 operacoes
    }
    //printf("%.15e\n", sum*2);
    return sum*2;
}

void aproxima_pi (double tolerancia) {

    DOUBLE_HEXA hex_baixo, hex_cima;
    ll count = 0, ulps = 0;
    double pi_aproximado_baixo, pi_aproximado_cima;

    fesetround(FE_DOWNWARD);
    pi_aproximado_baixo = somatoria(tolerancia, &count, 0);
    fesetround(FE_UPWARD);
    pi_aproximado_cima = somatoria(tolerancia, &count, 1);

    // Valor aproximado
    hex_baixo.value = pi_aproximado_baixo;
    hex_cima.value = pi_aproximado_cima;
    printf("%.15e %lX\n", hex_baixo.value, hex_baixo.hexa);
    printf("%.15e %lX\n", hex_cima.value, hex_cima.hexa);

    // ulps
    ulps = ABS(hex_cima.hexa, hex_baixo.hexa);
    printf("%lld\n", ulps);

    // Concertando o count
    count++;
    printf("%lld\n", count);
    return;
}

int main() {
    double entrada;
    scanf("%lf", &entrada);
    if (entrada == 0.0) {
        perror("Entrada invalida!\n");
        return 1;
    }
    // printf("entrada = %.15e\n", entrada);
    aproxima_pi(entrada);
    return 0;
}