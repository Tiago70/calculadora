#include <stdio.h>
#include "expressao.h"
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main (){
	setlocale (LC_ALL, "Portuguese");
	Expressao expressao1;
	
	char posFixa[100] = "2 3 + log 5 /";   // String de entrada aqui
	
	strcpy(expressao1.posFixa, posFixa);
	printf("Valor pos fixo: %s\n\n", expressao1.posFixa);
	
	expressao1.Valor = getValor(posFixa);
    printf("Resultado: %0.2f\n\n", expressao1.Valor);
	
    strcpy(expressao1.inFixa, getFormaInFixa(posFixa));
    printf("Infixa: %s", expressao1.inFixa);
    
    return 0;
}
