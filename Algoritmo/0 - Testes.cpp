#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Configuracoes.h"
#include "1 - EstruturasDeDados.cpp"
#include "2 - SuporteAStart.cpp"
#include "3 - AStar.cpp"
#include "4 - Auxiliares.cpp"

int main()
{
    // printMatriz(distancia_direta);
    // printf("\n\n\n");
    // printMatriz(distancia_real);

    // Testando criacao de uma lista
    node_list minha_lista;
    inicializar_lista(&minha_lista);

    node *nodo1 = adicionar_nodo(&minha_lista, "E1", 10.0, 5.0, 3.0, NULL);
    node *nodo2 = adicionar_nodo(&minha_lista, "E2", 45.0, 5.0, 3.0, nodo1);
    node *nodo3 = adicionar_nodo(&minha_lista, "E3", 30.0, 5.0, 3.0, nodo2);
    node *nodo4 = adicionar_nodo(&minha_lista, "E9", 14.0, 5.0, 3.0, nodo2);
    node *nodo5 = adicionar_nodo(&minha_lista, "E10", 14.0, 5.0, 3.0, nodo2);

    printf("Lista inicial:\n");
    apresentar_lista(&minha_lista);

    node_list nova_lista;
    inicializar_lista(&nova_lista);

    node *nodo6 = adicionar_nodo(&nova_lista, "E12", 42.0, 5.0, 3.0, NULL);
    node *nodo7 = adicionar_nodo(&nova_lista, "E11", 14.0, 5.0, 3.0, nodo1);

    // Testando segunda lista
    printf("\nLista 2:\n");
    apresentar_lista(&nova_lista);
    adicionar_lista(&minha_lista, &nova_lista);
    liberar_lista(&nova_lista);

    // Testando uniao de listas
    printf("\nUniao da lista 1 e 2:\n");
    apresentar_lista(&minha_lista);

    // Testando localizar o melhor nodo
    printf("\nMelhor nodo:\n");
    node *best_node = melhor_nodo(&minha_lista);
    apresentar_nodo(best_node);

    // Testando a busca por um nodo
    printf("\nTestando busca por um nodo: \n");
    apresentar_nodo(obter_nodo(&minha_lista, 3));

    // Testando funcao de nodo objetivo
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
    printf("\nTestes para o numero da estacao: \n");
    printf("E1 tem numero: %d\n", numero_estacao("E1")); // Deve retornar 1
    //printf("E15 tem numero: %d\n", numero_estacao("E15")); // Deve retornar ERRO
    printf("E10 tem numero: %d\n", numero_estacao("E10")); // Deve retornar 10
    printf("E3 tem numero: %d\n", numero_estacao("E3")); // Deve retornar 3
    //printf("A1 tem numero: %d\n", numero_estacao("A1")); // Deve retornar ERRO

    // Teste do calculo da heuristica
    printf("\nTestando obter a heuristica: \n");
    float h1 = calc_heuristica(nodo2);
    float h2 = calc_heuristica(nodo3);
    float h3 = calc_heuristica(nodo5);

    printf("Distancia direta de %s para %s: %.2f\n", nodo2->father->name, nodo2->name, h1);
    printf("Distancia direta de %s para %s: %.2f\n", nodo3->father->name, nodo3->name, h2);
    printf("Distancia direta de %s para %s: %.2f\n", nodo5->father->name, nodo5->name, h3);

    // Testa das matrizes diagonais
    printf("\nTeste das matrizes (diagonalidade): \n");
    testa_matriz_diagonal(distancia_direta);
    testa_matriz_diagonal(distancia_real);

    // Teste do calculo da distancia direta
    printf("\nTestando obter o tempo real: \n");
    float d1 = calc_travel_time(nodo2);
    float d2 = calc_travel_time(nodo3);
    float d3 = calc_travel_time(nodo5);

    printf("Distancia real de %s para %s: %.2f\n", nodo2->father->name, nodo2->name, d1);
    printf("Distancia real de %s para %s: %.2f\n", nodo3->father->name, nodo3->name, d2);
    printf("Distancia real de %s para %s: %.2f\n", nodo5->father->name, nodo5->name, d3);

    // Teste de adicionar nodo automaticamente
    // printf("\nTestando adicionar nodo automaticamente: \n");
    // adicionar_nodo_automaticamente(&minha_lista, nodo1);
    // apresentar_lista(&minha_lista);

    // Testando se de fato está sendo criada uma copia do nodo ao adicionar
    printf("\nTestando se de fato esta sendo criada uma copia do nodo ao adicionar:\n");
    node_list novissima_lista;
    inicializar_lista(&novissima_lista);
    node *nodo8 = adicionar_nodo(&novissima_lista, "E8", 14.0, 5.0, 3.0, nodo2);

    adicionar_nodo_automaticamente(&minha_lista, nodo8);

    liberar_lista(&novissima_lista);
    apresentar_lista(&minha_lista);

    // Testando funcao de gerar o nome da estacao
    printf("\nTestando funcao de gerar o nome da estacao:\n");
    printf("1 : %s\n", nome_estacao(1));
    printf("5 : %s\n", nome_estacao(5));
    printf("10 : %s\n", nome_estacao(10));

    // Testando a busca por nodos adjacentes
    node_list adjacentes;
    inicializar_lista(&adjacentes);
    buscar_nodos_adjacentes(nodo3, &adjacentes);
    apresentar_lista(&adjacentes);

    // Testando a função de contém nodo
    node_list lista_aleatoria;
    inicializar_lista(&lista_aleatoria);
    node *nodo9 = adicionar_nodo(&lista_aleatoria, "E14", 14.0, 5.0, 3.0, nodo2);

    printf("\nTestando funcao de contem nodo: \n");
    printf("Eh pra ser 1: %d\n", contem_nodo(&minha_lista, nodo1));
    printf("Eh pra ser 0: %d\n", contem_nodo(&minha_lista, nodo9));
    printf("Eh pra ser 1: %d\n", contem_nodo(&lista_aleatoria, nodo9));

    // Adicionando nodos que já existem
    printf("\nTestando se a adicao de listas esta tratando as repeticoes:\n");
    node_list lista_repetidos;
    inicializar_lista(&lista_repetidos);
    adicionar_nodo_automaticamente(&lista_repetidos, nodo1);
    adicionar_nodo_automaticamente(&lista_repetidos, nodo4);
    adicionar_nodo_automaticamente(&lista_repetidos, nodo9);
    
    printf("\nLista que sera adicionada: \n");
    apresentar_lista(&lista_repetidos);
    printf("\nLista alvo pre adicao:\n");
    apresentar_lista(&minha_lista);
    printf("\nResultado da adicao: \n");
    adicionar_lista(&minha_lista, &lista_repetidos);
    apresentar_lista(&minha_lista);

    // Testando a geracao do caminho
    resposta * res = gerar_resposta(nodo3);
    printf("\nTestando gerar a resposta: \n");
    printf("Caminho: %s\n", res->caminho);
    printf("Tempo aproximado: %.2f\n", res->tempo_total);

    // Testando baldeacao
    printf("\nTestando baldeacao: \n");
    printf("Naum pra ter: %d\n", tem_baldeacao(nodo1, nodo2));
    printf("Naum pra ter: %d\n", tem_baldeacao(nodo2, nodo3));
    printf("Eh pra ter: %d\n", tem_baldeacao(nodo2, nodo4));

    // Testando o A_Star
    printf("\n------------------------");
    printf("\nTestando A*: \n");
    // resposta * result = DEBUG_a_star();
    resposta * result = a_star();

    // Apresentando a resposta
    printf("\nResposta encontrada: \n");
    printf("%s\n", result->caminho);
    printf("%.2f\n", result->tempo_total);

    system("pause");

    return 0;
}
