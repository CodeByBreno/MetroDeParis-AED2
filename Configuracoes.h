#ifndef CONFIGURACOES_H
#define CONFIGURACOES_H

typedef struct node {
    char* name;          // Nome do nó
    float function;      // Valor da função f(n)
    float heuristic;     // Valor da heurística h(n)
    float distance;      // Distância g(n)
    struct node* father; // Ponteiro para o nó pai
} node;

typedef struct {
    node* elements;      // Ponteiro para o nodo inicial
    int size;            // Tamanho atual da lista
} node_list;

#endif // CONFIGURACOES_H