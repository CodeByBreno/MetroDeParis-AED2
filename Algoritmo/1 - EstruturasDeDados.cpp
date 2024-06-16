#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Configuracoes.h"

// Função para inicializar a lista
void inicializar_lista(node_list *lista)
{
    lista->head = (node *)malloc(sizeof(node));
    lista->size = 0;
}

// Função para adicionar um nó
node *adicionar_nodo(node_list *lista, const char *name, float function, float heuristic, float travel_time, node *father)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->name = strdup(name);
    new_node->function = function;
    new_node->heuristic = heuristic;
    new_node->travel_time = travel_time;
    new_node->father = father;

    if (lista->size == 0)
    {
        lista->head = new_node;
        new_node->next = NULL;
    }
    else
    {
        node *aux = lista->head;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = new_node;
        new_node->next = NULL;
    }
    lista->size++;

    return new_node;
}

node * adicionar_nodo_automaticamente(node_list * lista, node * nodo){
    node* newNode = adicionar_nodo(lista, nodo->name, nodo->function, nodo->heuristic, nodo->travel_time, nodo->father);
    return newNode;
}

// Função para liberar a lista
void liberar_lista(node_list *lista)
{
    node *current = lista->head;
    while (current != NULL)
    {
        node *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    lista->head = NULL;
}

// Função para remover um nó
void remover_nodo(node_list *lista, node *nodo)
{
    if (lista == NULL)
    {
        printf("Erro: Lista Inexistente");
        system("pause");
        exit(1);
    }

    if (lista->head == NULL)
    {
        printf("Erro: Lista Vazia");
        system("pause");
        exit(1);
    }

    node* atual = lista->head;
    node* anterior = NULL;

    while(atual != nodo){
        if (atual->father == nodo) {
            printf("Erro: O nodo nao pode ser removido porque existem outros relacionados a ele\n");
            system("pause");
            exit(1);
        }
        anterior = atual;
        atual = atual->next;
    }
    if (anterior != NULL){
        anterior->next = atual->next;
    } else {
        lista->head = atual->next;
    }

    free(atual);
}

// Obter um nodo da lista
node *obter_nodo(node_list *lista, int i)
{
    node *result = lista->head;

    if (i >= lista->size)
    {
        printf("Erro: Busca por nodo em posição inexistente na lista\n");
        system("pause");
        exit(1);
    }

    while (i > 0)
    {
        result = result->next;
        i--;
    }
    return result;
}

// Função para apresentar a lista
void apresentar_lista(node_list *lista)
{
    node *atual = lista->head;
    int i = 0;
    while (atual != NULL)
    {
        printf("%d - Nome: %s | F(n): %.2f | h(n): %.2f | d(n): %.2f | Father_name: %s\n",
               i++,
               atual->name,
               atual->function,
               atual->heuristic,
               atual->travel_time,
               atual->father ? atual->father->name : "NULL");
        atual = atual->next;
    }
}

// Mostra as informações de um nodo especifico
void apresentar_nodo(node *nodo)
{
    if (nodo == NULL)
    {
        printf("O nodo é NULL.\n");
        return;
    }

    printf("Nome: %s | F(n): %.2f | h(n): %.2f | d(n): %.2f | Father_name: %s\n",
           nodo->name,
           nodo->function,
           nodo->heuristic,
           nodo->travel_time,
           nodo->father ? nodo->father->name : "NULL");
}

void adicionar_lista(node_list* lista_recebe, node_list* lista_envia){
    node* aux = lista_envia->head;
    while(aux != NULL){
        adicionar_nodo(lista_recebe, aux->name, aux->function, aux->heuristic, aux->travel_time, aux->father);
        aux = aux->next;
    }
}