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

float calc_heuristica(node* nodo){
    if (nodo == NULL || nodo->father == NULL){
        printf("Erro: A heuristica não pode ser calculada para um nodo sem pai");
        system("pause");
        exit(3);
    }

    char* estacao_atual = (char *) malloc(sizeof(char)*strlen(nodo->name));
    strcpy(estacao_atual, nodo->name);
    
    char* estacao_anterior = (char *) malloc(sizeof(char)*strlen(nodo->father->name));
    strcpy(estacao_anterior, nodo->father->name);

    

}