#include "pi.h"

void arredondar (double valor, int casas_decimais) {
    DOUBLE_HEXA hex_baixo, hex_cima;

    double fator = pow(10, casas_decimais);

    int ulps;

    fesetround(FE_TOWARDZERO);
    hex_baixo.value = ((valor*fator) / fator);
    printf("%.15e %016X\n", hex_baixo.value, hex_baixo.hexa);

    fesetround(FE_TONEAREST);
    hex_cima.value = ((valor*fator) / fator);
    printf("%.15e %016X\n", hex_cima.value, hex_cima.hexa);

    ulps = ABS(hex_cima.hexa, hex_baixo.hexa);
    printf("%d\n", ulps);

}

double somatoria (double tolerancia) {
    ll it = 0;
    //printf("it = %lld\n", it);
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
        fat_Denominador *= (2*it) * (2*it + 1);
        diff = fabs((sum - pi_anterior)*2);
        //printf("valor diff = %.15e\n", sum);
    } while (diff > tolerancia);
    // printf("valor diff = %.15e\n", diff); 
    diference.value = diff;
    pi.value = fabs(sum*2 - M_PI);
    printf("%lld\n", it);
    printf("%.15e %016X\n", diff, diference.hexa);
    printf("%.15e %016X\n", fabs(sum*2 - M_PI), pi.hexa);
    return sum*2;
}

void aproxima_pi (double tolerancia) {
    
    double pi_aproximado;

    pi_aproximado = somatoria(tolerancia);
    // printf("pi = %.15e\n", pi_aproximado);
    arredondar(pi_aproximado, CASA_D);
    return;
}

int main() {
    double entrada;
    scanf("%lf", &entrada);
    // printf("entrada = %.15e\n", entrada);
    aproxima_pi(entrada);
    return 0;
}