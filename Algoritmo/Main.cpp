#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Configuracoes.h"
#include "1 - EstruturasDeDados.cpp"
#include "2 - SuporteAStart.cpp"
#include "3 - AStar.cpp"
#include "4 - Auxiliares.cpp"

int main(int argc, char *argv[]) {
    // Verifica se foram passados exatamente dois argumentos
    if (argc != 3) {
        return 1;  // Encerra o programa com código de erro
    }

    // Argumentos inicial e final recebidos do terminal
    initial_station = argv[1];
    final_station = argv[2];

    resposta * resultado = a_star();
    printf("%s", resultado->caminho);
    
    return 0;
}