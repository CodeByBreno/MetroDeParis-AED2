#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "Configuracoes.h"

node *maior_nodo(node_list *lista)
{
    float func_max = 0;
    node *best_node;
    node *aux = lista->head;
    while (aux != NULL)
    {
        if (aux->function > func_max)
        {
            func_max = aux->function;
            best_node = aux;
        }
        aux = aux->next;
    }
    return best_node;
}

int eh_nodo_objetivo(node *nodo)
{
    if ((nodo != NULL) &&
        (strcmp(nodo->name, final_station) == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

float calc_heuristica(node *nodo)
{
    if (nodo == NULL || nodo->father == NULL)
    {
        printf("Erro: A heuristica não pode ser calculada para um nodo sem pai");
        system("pause");
        exit(2);
    }

    char *estacao_atual = (char *)malloc(sizeof(char) * (strlen(nodo->name) + 1));
    strcpy(estacao_atual, nodo->name);

    char *estacao_anterior = (char *)malloc(sizeof(char) * (strlen(nodo->father->name) + 1));
    strcpy(estacao_anterior, nodo->father->name);

    int numero_estacao_atual = numero_estacao(estacao_atual) - 1;
    int numero_estacao_anterior = numero_estacao(estacao_anterior) - 1;

    float real_distance = distancia_direta[numero_estacao_atual][numero_estacao_anterior];
    return real_distance / train_speed;
}

float calc_travel_time(node *nodo)
{
    if (nodo == NULL || nodo->father == NULL)
    {
        printf("Erro: A heuristica não pode ser calculada para um nodo sem pai");
        system("pause");
        exit(2);
    }

    char *estacao_atual = (char *)malloc(sizeof(char) * (strlen(nodo->name) + 1));
    strcpy(estacao_atual, nodo->name);

    char *estacao_anterior = (char *)malloc(sizeof(char) * (strlen(nodo->father->name) + 1));
    strcpy(estacao_anterior, nodo->father->name);

    int numero_estacao_atual = numero_estacao(estacao_atual) - 1;
    int numero_estacao_anterior = numero_estacao(estacao_anterior) - 1;

    float distance = distancia_real[numero_estacao_atual][numero_estacao_anterior];

    if (distance == 0)
    {
        printf("Erro: Nao existe conexao entre essas duas estacoes\n");
        system("pause");
        exit(2);
    }

    return distance / train_speed;
}

void buscar_nodos_adjacentes(node *best_node, node_list *lista)
{
    if (best_node == NULL || lista == NULL)
    {
        printf("Erro: Dados nulos");
        system("pause");
        exit(2);
    }

    char *estacao = (char *)malloc(sizeof(char) * (strlen(best_node->name) + 1));
    strcpy(estacao, best_node->name);
    int numero_est = numero_estacao(estacao) - 1;

    // Começo identificando todos os números das estações adjacentes
    int estacoes_adjacentes[14];
    int j = 0;
    for (int i = numero_est; i < 14; i++)
    {
        if (distancia_real[numero_est][i] != 0)
        {
            estacoes_adjacentes[j++] = i;
        }
    }

    // "j" é o tamanho do vetor de estacoes adjacentes após a iterações acima
    for (int i = 0; i < j; i++)
    {
        adicionar_nodo(
            lista,
            nome_estacao(estacoes_adjacentes[i] + 1),
            0,0,0,
            best_node);
    }

    free(estacao);
    return;
}
