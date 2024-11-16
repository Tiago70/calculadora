#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>
#define PI 3.14159265358979323846

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

float getValor(char *Str){
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
                contadorPrincipal += 2;
                numerosEmPilha[numeroDeElementos-1] = log10(numerosEmPilha[numeroDeElementos-1]);
                break;
            case 's':
                contadorPrincipal += 2;
                numerosEmPilha[numeroDeElementos-1] = sin((PI/180) * numerosEmPilha[numeroDeElementos-1]);
                break;
            case 'c':
                contadorPrincipal += 2;
                numerosEmPilha[numeroDeElementos-1] = cos((PI/180) * numerosEmPilha[numeroDeElementos-1]);
                break;
            case 't':
                contadorPrincipal++;
                numerosEmPilha[numeroDeElementos-1] = tan((PI/180) * numerosEmPilha[numeroDeElementos-1]);
                break;
            default:
                break;
            }
        }
    }
    return numerosEmPilha[numeroDeElementos-1];
}
