#ifndef PILHA_HPP
#define PILHA_HPP

#include "Pacote.hpp"

class NoPilha {
public:
    Pacote* pacote;
    NoPilha* prox;
    NoPilha(Pacote* p);
};

class Pilha {
public:
    NoPilha* topo;
    int tamanho;
    Pilha();
    ~Pilha();
    void empilha(Pacote* p);
    Pacote* desempilha();
    bool estahVazia();
    Pacote* retiraMaisAntigo(int &custo);
};
    

#endif