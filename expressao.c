#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>
#define PI 3.14159265358979323846
#define MAX 100

static float *numerosEmPilha;

float SparaF(char numeroString[]){
    int contador, divisor = 0;
    double numero = numeroString[0] - '0';
    numero == -2 ? numero = 0 : numero;
    for (contador = 1; numeroString[contador] != '\0'; contador++)
    {   
        if (numeroString[contador] == '.'){
            divisor = strlen(numeroString)  - (contador + 1);
            continue;
        } 
        numero = numero * 10 + (numeroString[contador] - '0');
    }
    numero = numero / pow(10, divisor);
    return numero;
}

float getValor(char* Str){
    int contadorPrincipal, contadorNumero = 0, numeroGuardado = 0, numeroDeElementos = 1, tamanhoPadrao = 10;
    char numeroString[20];
    float numero;
    
    numerosEmPilha = malloc(tamanhoPadrao * sizeof(float));
    numerosEmPilha[0] = 0;

    for ( contadorPrincipal = 0; Str[contadorPrincipal] != '\0'; contadorPrincipal++)
    {   
        if (isdigit(Str[contadorPrincipal]) || Str[contadorPrincipal] == '.'){
            numeroGuardado = 0;
            numeroString[contadorNumero] = Str[contadorPrincipal];
            contadorNumero++;
        }
        else if(Str[contadorPrincipal] == 32){
            if (numeroGuardado) continue;
            numeroString[contadorNumero] = '\0';
            numeroGuardado = 1;
            contadorNumero = 0;
            if (numeroDeElementos >= tamanhoPadrao)
            {   
                tamanhoPadrao *= 2;
                numerosEmPilha = realloc(numerosEmPilha, tamanhoPadrao * sizeof(float));
            }
            numero = SparaF(numeroString);
            numerosEmPilha[numeroDeElementos] = numero;
            numeroDeElementos++;
        }
        else{
            if (numeroDeElementos == 0) continue;
            switch (Str[contadorPrincipal])
            {
            case '+':
                numeroDeElementos--;
                numerosEmPilha[numeroDeElementos-1] = numerosEmPilha[numeroDeElementos-1] + numerosEmPilha[numeroDeElementos];
                break;
            case '-':
                numeroDeElementos--;
                numerosEmPilha[numeroDeElementos-1] = numerosEmPilha[numeroDeElementos-1] - numerosEmPilha[numeroDeElementos];
                break;
            case '*':
                numeroDeElementos--;
                numerosEmPilha[numeroDeElementos-1] = numerosEmPilha[numeroDeElementos-1] * numerosEmPilha[numeroDeElementos];
                break;
            case '/':
                numeroDeElementos--;
                numerosEmPilha[numeroDeElementos-1] = numerosEmPilha[numeroDeElementos-1] / numerosEmPilha[numeroDeElementos];
                break;
            case '^':
                numeroDeElementos--;
                numerosEmPilha[numeroDeElementos-1] = pow(numerosEmPilha[numeroDeElementos-1], numerosEmPilha[numeroDeElementos]);
                break;
            case 'l':
                numerosEmPilha[numeroDeElementos-1] = log10(numerosEmPilha[numeroDeElementos-1]);
                break;
            case 's':
                numerosEmPilha[numeroDeElementos-1] = sin((PI/180) * numerosEmPilha[numeroDeElementos-1]);
                break;
            case 'c':
                numerosEmPilha[numeroDeElementos-1] = cos((PI/180) * numerosEmPilha[numeroDeElementos-1]);
                break;
            case 't':
                numerosEmPilha[numeroDeElementos-1] = tan((PI/180) * numerosEmPilha[numeroDeElementos-1]);
                break;
            case 'r':
                numerosEmPilha[numeroDeElementos-1] = sqrt(numerosEmPilha[numeroDeElementos-1]);
                break;
            default:
                break;
            }
        }
    }
    return numerosEmPilha[numeroDeElementos-1];
}

int verificaOperador(char* token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || 
            strcmp(token, "^") == 0 || strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tan") == 0 || 
            strcmp(token, "log") == 0);
}

static char* pilha[MAX];

char* getFormaInFixa(char* posFixa) {
    
    int topo = -1;

    char* token = strtok(posFixa, " ");
    
    while (token != NULL) {
        if (verificaOperador(token)) {

            if (strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tan") == 0 || strcmp(token, "log") == 0) {

                char* operador = pilha[topo--];
                int tamanho = strlen(operador) + strlen(token) + 3;
                char* infix = (char*)malloc(tamanho * sizeof(char));
                snprintf(infix, tamanho, "%s(%s)", token, operador);
                pilha[++topo] = infix;
                
            } else if (strcmp(token, "^") == 0) {  

                char* operand2 = pilha[topo--];
                char* operand1 = pilha[topo--];
                int tamanho = strlen(operand1) + strlen(operand2) + 4; 
                char* infix = (char*)malloc(tamanho * sizeof(char));
                snprintf(infix, tamanho, "(%s ^ %s)", operand1, operand2); 
                pilha[++topo] = infix;
                
            } else {

                char* operand2 = pilha[topo--];
                char* operand1 = pilha[topo--];
                int tamanho = strlen(operand1) + strlen(operand2) + 5; 
                char* infix = (char*)malloc(tamanho * sizeof(char));
                snprintf(infix, tamanho, "(%s %s %s)", operand1, token, operand2); 
                pilha[++topo] = infix;
            }
        } else {

            pilha[++topo] = token;
        }
        token = strtok(NULL, " ");
    }

    return pilha[topo];
}
