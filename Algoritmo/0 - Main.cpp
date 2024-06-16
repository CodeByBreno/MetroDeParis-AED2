#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Configuracoes.h"
#include "1 - EstruturasDeDados.cpp"
#include "2 - SuporteAStart.cpp"
#include "4 - Auxiliares.cpp"

void printMatriz(float matriz[14][14])
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            printf("%6.1f ", matriz[i][j]);
        }
        printf("\n");
    }
};

int main()
{
    // printMatriz(distancia_direta);
    // printf("\n\n\n");
    // printMatriz(distancia_real);

    node_list minha_lista;
    inicializar_lista(&minha_lista);

    node *nodo1 = adicionar_nodo(&minha_lista, "E1", 10.0, 5.0, 3.0, NULL);
    node *nodo2 = adicionar_nodo(&minha_lista, "E2", 45.0, 5.0, 3.0, nodo1);
    node *nodo3 = adicionar_nodo(&minha_lista, "E3", 30.0, 5.0, 3.0, nodo2);

    printf("Lista inicial:\n");
    apresentar_lista(&minha_lista);

    node_list nova_lista;
    inicializar_lista(&nova_lista);

    node *nodo1_lista2 = adicionar_nodo(&nova_lista, "E12", 42.0, 5.0, 3.0, NULL);
    node *nodo2_lista2 = adicionar_nodo(&nova_lista, "E11", 14.0, 5.0, 3.0, nodo1);

    printf("\nLista 2:\n");
    apresentar_lista(&nova_lista);
    adicionar_lista(&minha_lista, &nova_lista);
    liberar_lista(&nova_lista);

    printf("\nUniao da lista 1 e 2:\n");
    apresentar_lista(&minha_lista);

    printf("\nMelhor nodo:\n");
    node *best_node = maior_nodo(&minha_lista);
    apresentar_nodo(best_node);

    printf("\nTestando busca por um nodo: \n");
    apresentar_nodo(obter_nodo(&minha_lista, 3));

    printf("\nTestando se eh nodo objetivo: \n");
    printf("Nao deve ser. Resultado : %d\n", eh_nodo_objetivo(nodo1));
    printf("Deve ser. Resultado: %d\n", eh_nodo_objetivo(obter_nodo(&minha_lista, 3)));

    // Testes para a função valid_name
    printf("\nTestes para a funcao valid_name: \n");
    printf("E1 eh valido?: %d\n", valid_name("E1")); // Deve retornar 1
    printf("E15 eh valido?: %d\n", valid_name("E15")); // Deve retornar 0
    printf("E10 eh valido?: %d\n", valid_name("E10")); // Deve retornar 1
    printf("E3 eh valido?: %d\n", valid_name("E3")); // Deve retornar 1
    printf("A1 eh valido?: %d\n", valid_name("A1")); // Deve retornar 0

    // Testes para numero da estacao
    printf("E1 tem numero: %d\n", numero_estacao("E1")); // Deve retornar 1
    printf("E15 tem numero: %d\n", numero_estacao("E15")); // Deve retornar ERRO
    printf("E10 tem numero: %d\n", numero_estacao("E10")); // Deve retornar 10
    printf("E3 tem numero: %d\n", numero_estacao("E3")); // Deve retornar 3
    printf("A1 tem numero: %d\n", numero_estacao("A1")); // Deve retornar ERRO

    system("pause");

    return 0;
}
