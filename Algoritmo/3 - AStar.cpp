#include "Configuracoes.h"
#include "1 - EstruturasDeDados.cpp"

void a_star(){
    node_list fronteira;
    node_list visitados;
    inicializar_lista(&fronteira);
    inicializar_lista(&visitados);

    while(true){
        node nodoMaior = maiorNodo(fronteira);

        if (ehNodoObjetivo(nodoMaior)){
            return calcDistancia(nodoMaior);
        } else {
            removeNodoLista(fronteira, nodoMaior);
            
            node_list adjacentes;
            inicializar_lista(&adjacentes);

            buscarNodosAdjacentes(nodoMaior, &adjacentes);

            for(int i = 0; i < adjacentes.size; i++){
                float h = calcHeuristic(adjacentes.elements[i]);
                float d = calcDistancia(adjacentes.elements[i]);
                adjacentes.elements[i].heuristic = h;
                adjacentes.elements[i].distance = d;
                adjacentes.elements[i].function = h + d;
            }

            adicionarNodosFronteira(&fronteira, &adjacentes);
        }   

    }

}