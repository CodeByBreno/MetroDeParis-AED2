#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Configuracoes.h"
#include "1 - EstruturasDeDados.cpp"

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
    //printMatriz(distancia_direta);
    //printf("\n\n\n");
    //printMatriz(distancia_real);

    node_list minha_lista;
    inicializar_lista(&minha_lista);

    node* nodo1 = adicionar_nodo(&minha_lista, "Node1", 10.0, 5.0, 3.0, NULL);
    node* nodo2 = adicionar_nodo(&minha_lista, "Node2", 10.0, 5.0, 3.0, nodo1);
    node* nodo3 = adicionar_nodo(&minha_lista, "Node3", 10.0, 5.0, 3.0, nodo2);

    apresentar_lista(&minha_lista);

    node_list nova_lista;
    inicializar_lista(&nova_lista);

    node* nodo1_lista2 = adicionar_nodo(&nova_lista, "L2-Node1", 10.0, 5.0, 3.0, NULL);
    node* nodo2_lista2 = adicionar_nodo(&nova_lista, "L2-Node2", 10.0, 5.0, 3.0, nodo1);

    apresentar_lista(&nova_lista);
    adicionar_lista(&minha_lista, &nova_lista);
    liberar_lista(&nova_lista);
    apresentar_lista(&minha_lista);

    system("pause");

    return 0;
}
