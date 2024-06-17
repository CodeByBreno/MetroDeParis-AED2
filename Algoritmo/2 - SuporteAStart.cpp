#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "Configuracoes.h"

node *melhor_nodo(node_list *lista)
{
    float func_max = 100000;
    node *best_node;
    node *aux = lista->head;
    while (aux != NULL)
    {
        if (aux->function < func_max)
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
        lancar_erro("Erro: A heuristica não pode ser calculada para um nodo sem pai\n", 10);

    char *estacao_atual = (char *)malloc(sizeof(char) * (strlen(nodo->name) + 1));
    strcpy(estacao_atual, nodo->name);

    char *estacao_anterior = (char *)malloc(sizeof(char) * (strlen(nodo->father->name) + 1));
    strcpy(estacao_anterior, nodo->father->name);

    int numero_estacao_atual = numero_estacao(estacao_atual) - 1;
    int numero_estacao_anterior = numero_estacao(estacao_anterior) - 1;

    float real_distance = distancia_direta[numero_estacao_atual][numero_estacao_anterior];
    return real_distance / train_speed * 60; // convertendo o resultado de horas para minutos
}

float calc_travel_time(node *nodo)
{
    if (nodo == NULL || nodo->father == NULL)
        lancar_erro("Erro: A heuristica não pode ser calculada para um nodo sem pai\n", 11);

    char *estacao_atual = (char *)malloc(sizeof(char) * (strlen(nodo->name) + 1));
    strcpy(estacao_atual, nodo->name);

    char *estacao_anterior = (char *)malloc(sizeof(char) * (strlen(nodo->father->name) + 1));
    strcpy(estacao_anterior, nodo->father->name);

    int numero_estacao_atual = numero_estacao(estacao_atual) - 1;
    int numero_estacao_anterior = numero_estacao(estacao_anterior) - 1;

    float distance = distancia_real[numero_estacao_atual][numero_estacao_anterior];

    if (distance == 0)
        lancar_erro("Erro: Nao existe conexao entre essas duas estacoes\n", 12);

    return distance / train_speed * 60; // convertendo o resultado de horas para minutos
}

void buscar_nodos_adjacentes(node *best_node, node_list *lista)
{
    if (best_node == NULL || lista == NULL)
        lancar_erro("Erro: Dados nulos\n", 13);

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

    // Se não houve nenhum adjacente, a lista deve ter ponteiro de cabeçalho nulo
    if (j == 0)
    {
        lista->head = NULL;
    }
    else
    {
        // "j" é o tamanho do vetor de estacoes adjacentes após a iterações acima
        for (int i = 0; i < j; i++)
        {
            adicionar_nodo(
                lista,
                nome_estacao(estacoes_adjacentes[i] + 1),
                0, 0, 0,
                best_node);
        }
    }

    free(estacao);
    return;
}

resposta *gerar_resposta(node *nodo)
{
    if (nodo == NULL) 
        lancar_erro("Erro: Nodo nulo\n", 14);

    // Primeiro passo: determinar o tamanho total necessário
    node *aux = nodo;
    int total_length = 0;
    int num_nodes = 0;
    while (aux != NULL) {
        total_length += strlen(aux->name) + 1; // +1 para a vírgula ou terminador nulo
        aux = aux->father;
        num_nodes++;
    }

    // Alocar memória para o resultado
    resposta *result = (resposta *)malloc(sizeof(resposta));
    if (result == NULL)
        lancar_erro("Erro: Falha ao alocar memória para resultado\n", 15);

    result->caminho = (char *)malloc(sizeof(char) * (total_length + 1)); // +1 para o terminador nulo
    if (result->caminho == NULL) 
        lancar_erro("Erro: Falha ao alocar memória para caminho\n", 16);

    result->caminho[0] = '\0'; // Inicializa a string vazia

    // Segundo passo: preencher a string na ordem correta
    char **lista_caminho = NULL;  
    int counter = 0;
    aux = nodo;

    while (aux != NULL) {
        lista_caminho = (char **)realloc(lista_caminho, sizeof(char*) * (counter + 1));
        if (lista_caminho == NULL) 
            lancar_erro("Erro: Falha ao realocar lista_caminho\n", 17);
        
        lista_caminho[counter] = (char *)malloc(sizeof(char) * (strlen(aux->name) + 1));
        if (lista_caminho[counter] == NULL) 
            lancar_erro("Erro: Falha ao alocar memória para lista_caminho\n", 18);
        
        strcpy(lista_caminho[counter], aux->name);
        counter++;
        aux = aux->father;
    }

    // Imprime os elementos da lista na ordem correta
    for (int i = counter - 1; i >= 0; i--) {
        //printf("%s%s", lista_caminho[i], (i > 0) ? "," : "");
        strcat(result->caminho, lista_caminho[i]);
        if (i > 0) {
            strcat(result->caminho, ",");
        }
    }

    result->tempo_total = nodo->travel_time;

    // Libera memória alocada para lista_caminho
    for (int i = 0; i < counter; i++) {
        free(lista_caminho[i]);
    }
    free(lista_caminho);

    return result;
}

int tem_baldeacao(node * inicio, node * fim){
    if (inicio == NULL || 
        fim == NULL || 
        inicio->father == NULL ||
        fim->father != inicio){
        return 0;
    }

    int estacao1 = numero_estacao(inicio->father->name);
    int estacao2 = numero_estacao(inicio->name);
    int estacao3 = numero_estacao(fim->name);

    int linha1 = linha_metro[estacao1][estacao2];
    int linha2 = linha_metro[estacao2][estacao3];

    if (linha1 != linha2)
        return 1;
    else    
        return 0;
}