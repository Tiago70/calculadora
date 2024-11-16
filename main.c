#include <stdio.h>
#include "expressao.h"
#include <stdlib.h>

int main (){
    float resultado;
    resultado = getValor("10 log 3 ^ 2 +");
    printf("Resultado: %f", resultado);

    // resultado = getValor("8 5 2 4 + * +");
    // printf("Resultado: %0.2f", resultado);
    // system("pause");
    return 0;
}
