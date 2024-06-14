#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Configuracoes.h"

// Função para adicionar as informações passadas ao ponteiro do nodo
void createNode(node* newNode, const char* name, float function, float heuristic, float distance, node* father) {
    newNode->name = (char*)malloc(strlen(name) + 1); 
    if (newNode->name == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o nome.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->name, name);
    newNode->function = function;
    newNode->heuristic = heuristic;
    newNode->distance = distance;
    newNode->father = father;
};

// Inicializa uma lista de nodos com tamanho vazio e nenhum elemento inicial
void inicializar_lista(node_list* entrada) {
    entrada->elements = NULL;
    entrada->size = 0;
};

// Adiciona um novo nodo a lista, atualizando seu tamanho automaticamente
void adicionar_nodo(node_list* entrada, const char* name, float function, float heuristic, float distance, node* father) {
    entrada->elements = (node*)realloc(entrada->elements, (entrada->size + 1) * sizeof(node));
    if (entrada->elements == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a lista de nós.\n");
        exit(EXIT_FAILURE);
    }
    createNode(&entrada->elements[entrada->size], name, function, heuristic, distance, father);
    entrada->size++;
};

// Apresenta a lista de nodos no terminal. Recebe um ponteiro para a lista a ser mostrada
void apresentar_lista(node_list* entrada) {
    printf("Tamanho: %d\n", entrada->size);
    for (int i = 0; i < entrada->size; i++) {
        printf("Nome: %s | F(n): %.2f | h(n): %.2f | d(n): %.2f | Father_name: %s\n",
               entrada->elements[i].name,
               entrada->elements[i].function,
               entrada->elements[i].heuristic,
               entrada->elements[i].distance,
               entrada->elements[i].father ? entrada->elements[i].father->name : "NULL");
    }
};

// Apresenta uma nodo isolado. Recebe um ponteiro para a nodo a ser mostrado
void apresentar_nodo(node* nodo){
    printf("Nome: %s\n", nodo->name);
    printf("Função: %.2f\n", nodo->function);
    printf("Heurística: %.2f\n", nodo->heuristic);
    printf("Distância: %.2f\n", nodo->distance);
    printf("Pai: %p\n", (void*)nodo->father);
};

// Libera o espaço alocado em memória para a lista. Recebe um ponteiro para a lista de nodos
void liberar_lista(node_list* entrada) {
    for (int i = 0; i < entrada->size; i++) {
        free(entrada->elements[i].name);
    }
    free(entrada->elements);
    entrada->elements = NULL;
    entrada->size = 0;
};
