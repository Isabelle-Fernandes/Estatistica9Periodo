#include <iostream>
#include <string>
#include "heap.hpp"
#include "unionFind.hpp"

int main() { 

    int tamVertices, tamArestas;

    std::cin >> tamVertices >> tamArestas;

    Heap heap = Heap(tamArestas);

    for (int i = 0; i < tamArestas; i++) {
        Aresta aresta;   
        std::cin >> aresta.u >> aresta.v >> aresta.custo;
        heap.Insere(aresta);
    }

    UnionFind unionFind = UnionFind(tamVertices);

    int limiteTamArestas = tamArestas - 1;
    int arestasAdicionadas = 0;
    int custoTotal = 0;
 
    while (arestasAdicionadas <= limiteTamArestas && heap.tamAtual > 0) {
        Aresta aresta = heap.Remove();
        int raizU = unionFind.Find(aresta.u);
        int raizV = unionFind.Find(aresta.v);
        if (raizU != raizV) {
            unionFind.Union(aresta.u, aresta.v);
            custoTotal += aresta.custo; 
            arestasAdicionadas++;       
        }
    }
    std::cout << custoTotal << std::endl;
}

