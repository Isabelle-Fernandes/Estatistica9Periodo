#ifndef HEAP_HPP
#define HEAP_HPP
#include "unionFind.hpp"

class Heap {
public:
    Heap(int tamanho);
    Aresta* aresta;
    int tamAtual;
    int GetAncestral(int i);
    int GetSucessorEsq(int i);
    int GetSucessorDir(int i);
    void Insere(Aresta x);
    int GetMenorSucessor(int i);
    void Conserta();
    Aresta Remove();
};

#endif