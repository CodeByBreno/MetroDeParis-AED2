#ifndef CONFIGURACOES_H
#define CONFIGURACOES_H

char initial_station[4];
char final_station[4] = "E12";
typedef struct node {
    char* name;          // Nome do nó
    float function;      // Valor da função f(n)
    float heuristic;     // Valor da heurística h(n)
    float travel_time;      // Distância g(n)
    struct node* father; // Ponteiro para o nó pai
    struct node* next;  // Próximo nodo da lista ligada
} node;

typedef struct {
    node* head;
    int size; // Tamanho atual da lista ligada
} node_list;

// Estruturas de Dados
void inicializar_lista(node_list *lista) ;
node* adicionar_nodo(node_list *lista, const char *name, float function, float heuristic, float travel_time, node *father);
void liberar_lista(node_list *lista);
void apresentar_lista(node_list *lista);
void remover_nodo(node_list *entrada, node *nodo);
node* obter_nodo(node_list * lista, int i);
void apresentar_nodo(node *nodo);

// Funções de Suporte para o AStar
node* maior_nodo(node_list * lista);
int eh_nodo_objetivo(node *nodo);
float calc_heuristica(node* nodo);
float calc_travel_time(node* nodo);
void buscar_nodos_adjacentes(nodo* best_node, node_list* lista);

// Funções secundárias auxiliares
int valid_name(const char *name);
int numero_estacao(const char *name);
int testa_matriz_diagonal(float ** matriz, int n, int m);

// Dados do problema
float train_speed = 8.33; // Velocidade em m/s (30km/h)
float change_line_time = 4.0;

float distancia_direta[14][14] = {
    {0, 10, 18.5, 24.8, 36.4, 38.8, 35.8, 25.4, 17.6, 9.1, 16.7, 27.3, 27.6, 29.8},
    {10, 0, 8.5, 14.8, 26.6, 29.1, 26.1, 17.3, 10, 3.5, 15.5, 20.9, 19.1, 21.8},
    {18.5, 8.5, 0, 6.3, 18.2, 20.6, 17.6, 13.6, 9.4, 10.3, 19.5, 19.1, 12.1, 16.6},
    {24.8, 14.8, 6.3, 0, 12, 14.4, 11.5, 12.4, 12.6, 16.7, 23.6, 18.6, 10.6, 15.4},
    {36.4, 26.6, 18.2, 12, 0, 3, 2.4, 19.4, 23.3, 28.2, 34.2, 24.8, 14.5, 17.9},
    {38.8, 29.1, 20.6, 14.4, 3, 0, 3.3, 22.3, 25.7, 30.3, 36.7, 27.6, 15.2, 18.2},
    {35.8, 26.1, 17.6, 11.5, 2.4, 3.3, 0, 20, 23, 27.3, 34.2, 25.7, 12.4, 15.6},
    {25.4, 17.3, 13.6, 12.4, 19.4, 22.3, 20, 0, 8.2, 20.3, 16.1, 6.4, 22.7, 27.6},
    {17.6, 10, 9.4, 12.6, 23.3, 25.7, 23, 8.2, 0, 13.5, 11.2, 10.9, 21.2, 26.6},
    {9.1, 3.5, 10.3, 16.7, 28.2, 30.3, 27.3, 20.3, 13.5, 0, 17.6, 24.2, 18.7, 21.2},
    {16.7, 15.5, 19.5, 23.6, 34.2, 36.7, 34.2, 16.1, 11.2, 17.6, 0, 14.2, 31.5, 35.5},
    {27.3, 20.9, 19.1, 18.6, 24.8, 27.6, 25.7, 6.4, 10.9, 24.2, 14.2, 0, 28.8, 33.6},
    {27.6, 19.1, 12.1, 10.6, 14.5, 15.2, 12.4, 22.7, 21.2, 18.7, 31.5, 28.8, 0, 5.1},
    {29.8, 21.8, 16.6, 15.4, 17.9, 18.2, 15.6, 27.6, 26.6, 21.2, 35.5, 33.6, 5.1, 0}};

float distancia_real[14][14] = {
    {   0,   10,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0},
    {  10,    0,  8.5,    0,    0,    0,    0,    0,   10,  3.5,    0,    0,    0,    0},
    {   0,  8.5,    0,  6.3,    0,    0,    0,    0,  9.4,    0,    0,    0, 18.7,    0},
    {   0,    0,  6.3,    0,   13,    0,    0, 15.3,    0,    0,    0,    0, 12.8,    0},
    {   0,    0,    0,   13,    0,    3,  2.4,   30,    0,    0,    0,    0,    0,    0},
    {   0,    0,    0,    0,    3,    0,    0,    0,    0,    0,    0,    0,    0,    0},
    {   0,    0,    0,    0,  2.4,    0,    0,    0,    0,    0,    0,    0,    0,    0},
    {   0,    0,    0, 15.3,   30,    0,    0,    0,  9.6,    0,    0,  6.4,    0,    0},
    {   0,   10,  9.4,    0,    0,    0,    0,  9.6,    0,    0, 12.2,    0,    0,    0},
    {   0,  3.5,    0,    0,    0,    0,    0,    0,    0,    0,     0,   0,    0,    0},
    {   0,    0,    0,    0,    0,    0,    0,    0, 12.2,    0,     0,   0,    0,    0},
    {   0,    0,    0,    0,    0,    0,    0,  6.4,    0,    0,     0,   0,    0,    0},
    {   0,    0, 18.7, 12.8,    0,    0,    0,    0,    0,    0,     0,    0,   0,  5.1},
    {   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,     0,    0, 5.1,    0}};


int linha_metro[14][14] = {
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0},
    {0, 0, 1, 0, 1, 0, 0, 4, 0, 0, 0, 0, 4, 0},
    {0, 0, 0, 1, 0, 1, 2, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 4, 2, 0, 0, 0, 2, 0, 0, 4, 0, 0},
    {0, 2, 3, 0, 0, 0, 0, 2, 0, 0, 3, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
    {0, 0, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0}};

#endif // CONFIGURACOES_H
