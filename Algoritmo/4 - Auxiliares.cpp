#include "stdlib.h"
#include "string.h"
#include "stdio.h"

// Avalia se o nome da estação utilizado é válido
int valid_name(const char *name)
{
    const char *validos[] = {"E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10", "E11", "E12", "E13", "E14"};
    int flag = 0;

    for (int i = 0; i < 14; i++)
    {
        if (strcmp(validos[i], name) == 0)
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

// Converete o nome da estação em um numero
int numero_estacao(const char *name)
{
    const char *validos[] = {"E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "E10", "E11", "E12", "E13", "E14"};
    int c = 0;

    if (valid_name(name) == 0){
        printf("Erro: Nome da estacao invalido\n");
        system("pause");
        exit(4);
    }

    for (int i = 0; i < 14; i++)
    {
        c++;
        if (strcmp(validos[i], name) == 0)
        {
            break;
        }
    }

    return c;
}

int testa_matriz_diagonal(float matriz[14][14]){
    for (int i = 0; i < 14; i++){
        for(int j = 0; j < 14; j++){
            if (matriz[i][j] != matriz[j][i]){
                printf("Nao eh simetrica pela diagonal. Erro em (%d, %d): %.2f\n", i, j, matriz[i][j]);
            }
        }
    }
    printf("Eh simetrica pela diagonal\n");
}