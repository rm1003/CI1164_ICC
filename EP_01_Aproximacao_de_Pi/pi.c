#include "pi.h"


double somatoria (double tolerancia, ll *count, int mode) {

    ll it = 0;
    ll two_it = 0;
    ull pow_2k = 1; // 2^k

    double fat_k = 1; // k!
    double fat_Denominador = 1; // (2k + 1)!
    double sum = 0.0;
    double pi_anterior, diff;

    tolerancia /= 2; // 1 operacao de double

    DOUBLE_HEXA diference, pi;

    do {
        pi_anterior = sum;
        sum += ((pow_2k*fat_k*fat_k) / fat_Denominador); // 4 operacoes de double

        it++; // operacao de long long

        fat_k *= it; // 1 operacao de double
        pow_2k *= 2; // operacao de unsigned long long

        two_it = 2*it; // operacao de long long
        fat_Denominador *= (two_it * (two_it + 1)); // 1 operacao de double

        diff = ABS(sum, pi_anterior); // 1 operacao de double 

        // Contagem apenas no arredondamento para cima
        if (mode != 0) (*count) += 7;
    
        // total 7 operacoes dentro do loop
    } while (diff >= tolerancia);

    sum *= 2; // 1 operacoes

    if (mode != 0) {
        // Erros
        diference.value = diff*2; // 1 operacao de double
        pi.value = ABS(sum, M_PI); // 1 operacoes de double
        
        printf("%lld\n", it);
        printf("%.15e %lX\n", diference.value, diference.hexa);
        printf("%.15e %lX\n", pi.value, pi.hexa);

        (*count) += 4; // dentro do if + sum*2 + tolerancia/2 sao 4 operacoes
    }

    return sum;
}

void aproxima_pi (double tolerancia) {

    DOUBLE_HEXA hex_baixo, hex_cima;
    ll count = 0, ulps = 0;

    // Aproximacao para baixo
    fesetround(FE_DOWNWARD);
    hex_baixo.value = somatoria(tolerancia, &count, 0);

    // Aproximacao para cima
    fesetround(FE_UPWARD);
    hex_cima.value = somatoria(tolerancia, &count, 1);

    // Valor aproximado
    printf("%.15e %lX\n", hex_baixo.value, hex_baixo.hexa);
    printf("%.15e %lX\n", hex_cima.value, hex_cima.hexa);

    // ulps
    ulps = ABS(hex_cima.hexa, hex_baixo.hexa);
    printf("%lld\n", ulps);

    // FLOPs
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
    if (entrada <= 1e-16) {
        perror("Entrada invalida!\n");
        return 2;
    }

    aproxima_pi(entrada);
    return 0;
}