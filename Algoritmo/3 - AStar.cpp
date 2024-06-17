#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "Configuracoes.h"

resposta * a_star(){
    node_list fronteira;
    node_list visitados;
    inicializar_lista(&fronteira);
    inicializar_lista(&visitados);

    adicionar_nodo(&fronteira, initial_station, 0, 0, 0, NULL);

    node * nodo_objetivo = create_node(final_station, 0, 0, 0, NULL);

    int limitador = 0;
    while(limitador++ < 100){
        node * melhorNodo = melhor_nodo(&fronteira);

        if (fronteira.size == 0){
            printf("Erro: Nao existe rota entre as estacoes\n");
            system("pause");
            exit(19);
        }

        if (contem_nodo(&fronteira, nodo_objetivo)){
            node* objetivo = obter_nodo_pelo_nome(&fronteira, final_station);
            resposta * result = gerar_resposta(objetivo);

            return result;
        } else {
            node* best_node = adicionar_nodo_automaticamente(&visitados, melhorNodo);
            remover_nodo(&fronteira, melhorNodo);
            
            node_list adjacentes;
            inicializar_lista(&adjacentes);
            buscar_nodos_adjacentes(best_node, &adjacentes);

            for(int i = 0; i < adjacentes.size; i++){
                node * atual = obter_nodo(&adjacentes, i);

                float heuristic = calc_heuristica(atual);
                atual->heuristic = heuristic;

                float time = calc_travel_time(atual);
                if (tem_baldeacao(atual->father, atual)){
                    time += 4;
                }
                atual->travel_time = time + atual->father->travel_time;
                
                atual->function = atual->heuristic + atual->travel_time;
            }

            adicionar_lista(&fronteira, &adjacentes);
        }   
    }

    printf("Erro: Nao foi possivel encontrar um caminho\n");
    system("pause");
    exit(20);
}

resposta * DEBUG_a_star(){
    node_list fronteira;
    node_list visitados;
    inicializar_lista(&fronteira);
    inicializar_lista(&visitados);

    adicionar_nodo(&fronteira, initial_station, 0, 0, 0, NULL);

    node * nodo_objetivo = create_node(final_station, 0, 0, 0, NULL);

    int limitador = 0;
    while(limitador++ < 10){
        node * melhorNodo = melhor_nodo(&fronteira);

        if (fronteira.size == 0){
            printf("Erro: Nao existe rota entre as estacoes\n");
            system("pause");
            exit(21);
        }

        printf("\n-------------------------------\n");
        printf("\nMelhor nodo da rodada: \n");
        apresentar_nodo(melhorNodo);

        if (contem_nodo(&fronteira, nodo_objetivo)){
            printf("\nNodo objetivo encontrado!\n");
            node* objetivo = obter_nodo_pelo_nome(&fronteira, final_station);
            resposta * result = gerar_resposta(objetivo);

            return result;
        } else {
            node* best_node = adicionar_nodo_automaticamente(&visitados, melhorNodo);
            remover_nodo(&fronteira, melhorNodo);
            
            node_list adjacentes;
            inicializar_lista(&adjacentes);
            buscar_nodos_adjacentes(best_node, &adjacentes);

            for(int i = 0; i < adjacentes.size; i++){
                node * atual = obter_nodo(&adjacentes, i);
    
                float heuristic = calc_heuristica(atual);
                atual->heuristic = heuristic;

                float time = calc_travel_time(atual);
                if (tem_baldeacao(atual->father, atual)){
                    printf("Vindo de %s, Baldeacao de %s para %s\n", atual->father->father->name, atual->father->name, atual->name);
                    time += 4;
                }
                atual->travel_time = time + atual->father->travel_time;
                
                atual->function = atual->heuristic + atual->travel_time;
            }

            adicionar_lista(&fronteira, &adjacentes);

            printf("\nAdjacentes a %s: \n", best_node->name);
            apresentar_lista(&adjacentes);

            printf("\nFronteira: \n");
            apresentar_lista(&fronteira);
            printf("\nLista de nodos visitados: \n");
            apresentar_lista(&visitados);
        }   
    }

    printf("Erro: Nao foi possivel encontrar um caminho\n");
    system("pause");
    exit(22);
}