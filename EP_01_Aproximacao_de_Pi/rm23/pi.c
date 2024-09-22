#include "pi.h"

void arredondar (double valor) {
    DOUBLE_HEXA hex_baixo, hex_cima;
  
    double fator = 10.0;
    int ulps;

    fesetround(FE_DOWNWARD);
    hex_baixo.value = (valor*fator)/fator;
    printf("%.15e %lX\n", hex_baixo.value, hex_baixo.hexa);


    fesetround(FE_UPWARD);
    hex_cima.value = (valor*fator)/fator;
    printf("%.15e %lX\n", hex_cima.value, hex_cima.hexa);

    if (hex_cima.hexa == hex_baixo.hexa) {
        printf("0\n");
        return;
    }

    ulps = ABS(hex_cima.hexa, hex_baixo.hexa);
    printf("%d\n", ulps);
    return;
}

double somatoria (double tolerancia, ll *count) {
    ll it = 0;
    
    double pow_2k = 1; // 2^k
    double fat_k = 1; // k!
    double fat_Denominador = 1; // (2k + 1)!
    double sum = 0.0;
    double termo, pi_anterior, diff;

    DOUBLE_HEXA diference, pi;

    do {
        termo = ((pow_2k*fat_k*fat_k) / fat_Denominador);
        pi_anterior = sum;
        sum += termo;
        it++;
        fat_k *= it;
        pow_2k *= 2;
        fat_Denominador *= ((2*it) * ((2*it) + 1));
        diff = fabs(sum - pi_anterior)*2;
        (*count) += 10;
        
    } while (diff >= tolerancia);
    
    diference.value = diff;
    pi.value = fabs((sum*2) - M_PI);
    printf("%lld\n", it);
    printf("%.15e %lX\n", diference.value, diference.hexa);
    printf("%.15e %lX\n", fabs((sum*2) - M_PI), pi.hexa);

    //printf("%.15e\n", sum*2);
    return sum*2;
}

void aproxima_pi (double tolerancia) {
    
    ll count = 0;
    double pi_aproximado;

    pi_aproximado = somatoria(tolerancia, &count);
    
    arredondar(pi_aproximado);
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