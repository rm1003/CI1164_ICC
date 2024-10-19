#include "includes.h"

int main () {
    ll n; scanf("%lld", &n);
    PSISTEMA_LINEAR sistema = init_system(n);
    output(sistema);
    free_SL(sistema);
    return 0;
}