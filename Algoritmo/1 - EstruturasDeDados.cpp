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

node * create_node(const char *name, float function, float heuristic, float travel_time, node *father){
    node *new_node = (node *)malloc(sizeof(node));
    if (name == NULL){
        printf("Erro: Adicionando Nodo com nome nulo\n");
        system("pause");
        exit(1);
    }
    new_node->name = strdup(name);
    new_node->function = function;
    new_node->heuristic = heuristic;
    new_node->travel_time = travel_time;
    new_node->father = father;
    return new_node;
}

// Função para adicionar um nó
node *adicionar_nodo(node_list *lista, const char *name, float function, float heuristic, float travel_time, node *father)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (name == NULL){
        printf("Erro: Adicionando Nodo com nome nulo\n");
        system("pause");
        exit(2);
    }
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
    if (contem_nodo(lista, nodo)){
        printf("Erro: Nodo ja contido na lista (outro nodo de mesmo nome esta presente)\n");
        system("pause");
        exit(3);
    }

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
        printf("Erro: Lista Inexistente\n");
        system("pause");
        exit(4);
    }

    if (lista->head == NULL)
    {
        printf("Erro: Lista Vazia\n");
        system("pause");
        exit(5);
    }

    node* atual = lista->head;
    node* anterior = NULL;

    while(atual != nodo){
        if (atual->father == nodo) {
            printf("Erro: O nodo nao pode ser removido porque existem outros relacionados a ele\n");
            system("pause");
            exit(6);
        }
        anterior = atual;
        atual = atual->next;
    }
    if (anterior != NULL){
        anterior->next = atual->next;
    } else {
        lista->head = atual->next;
    }

    lista->size--;

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
        exit(7);
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

// Adiciona o conteúdo da segunda lista de nodos diretamente na primeira
void adicionar_lista(node_list* lista_recebe, node_list* lista_envia){
    node* aux = lista_envia->head;

    // Remove da lista de envio os nodos que já estão na lista que irá receber
    node_list lista_envio_tratada;
    inicializar_lista(&lista_envio_tratada);
    while (aux != NULL){
        if (contem_nodo(lista_recebe, aux) == 0){
            adicionar_nodo_automaticamente(&lista_envio_tratada, aux);
        };
        aux = aux->next;
    }

    // Agora varro a lista tratada, adicionando todos os nodos dela à lista alvo
    aux = lista_envio_tratada.head;
    if (lista_envio_tratada.size == 0) {
        return;
    }

    while(aux != NULL){
        adicionar_nodo(lista_recebe, aux->name, aux->function, aux->heuristic, aux->travel_time, aux->father);
        aux = aux->next;
    }
}

// Verifica se a lista já contém um nodo de MESMO NOME que o passado
// Se a lista ou o nodo passado forem nulos, ou se o campo name não for informado, é retornado FALSO (0)
int contem_nodo(node_list * lista, node * nodo){
    if (lista == NULL || 
        nodo == NULL || 
        nodo->name == NULL) {
        return 0;
    }

    node * aux = lista->head;
    if (lista->size == 0){
        return 0;
    }

    while(aux != NULL){
        if (aux->name == NULL){
            printf("Erro: Nodo com nome nulo\n");
            system("pause");
            exit(8);
        }

        if (strcmp(aux->name, nodo->name) == 0){
            return 1;
        } else {
            aux = aux->next;
        }
    }
    return 0;
}

node * obter_nodo_pelo_nome(node_list * lista, char * nome){
    node * aux = lista->head;
    while(aux != NULL){
        if (strcmp(aux->name, nome) == 0){
            return aux;
        }
        aux = aux->next;
    }
    
    printf("Erro: Busca por nodo com nome inexistente na lista\n");
    system("pause");
    exit(9);
}