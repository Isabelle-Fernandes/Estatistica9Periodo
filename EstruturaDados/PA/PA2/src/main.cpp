#include "Grafo.hpp"
#include <iostream>
#include <string>

#define DADO_BASICO "-d"
#define VIZINHACA "-n"
#define COMPLETO "-k" 

int main(int argc, char* argv[]) { 

    if (argc != 2) {  
        return 1;
    }

    Menu menu;
    Grafo grafo = menu.criaGrafo();

    std::string comando = argv[1];

    if (comando == DADO_BASICO) {
        menu.ImprimeDadoBasico(&grafo);
    } else if (comando == VIZINHACA) {
        menu.ImprimeVizinhos(&grafo);
    } else if (comando == COMPLETO) {
        int quantidadeGrafoCompleto = (grafo.QuantidadeVertices() * (grafo.QuantidadeVertices() - 1)) / 2;
        if (grafo.QuantidadeArestas() == quantidadeGrafoCompleto)
            std::cout << 1 << std::endl;
        else
            std::cout << 0 << std::endl;
    } else {
        return 1;
    }

    return 0;
}
