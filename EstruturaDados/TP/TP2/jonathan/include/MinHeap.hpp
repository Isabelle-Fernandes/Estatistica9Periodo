#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "Evento.hpp"

class MinHeap {
private:
    Evento heap[10000];
    int tamanho;
    void corrigeSubindo(int i);
    void corrigeDescendo(int i);
    bool compara(const Evento& a, const Evento& b);
public:
    MinHeap();
    void insere(const Evento& e);
    Evento retira();
    bool vazio() const;
};

#endif
