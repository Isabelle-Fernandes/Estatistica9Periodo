#ifndef VETOR_H
#define VETOR_H

#include "Item.hpp"

#ifndef VETSZ
#define VETSZ 6 
#endif


class Vetor {
public:
    Vetor(const Vetor &copia); // construtor de copia de um vetor para o outro
    Vetor(int seed_);

    Item itens[VETSZ];
    int tam;

    int chamadas;
    int comparacoes;
    int movimentacoes;
 
    void inccalls(int num);
    void inccmp(int num);
    void incmov(int num);
    void resetCounter();
    void InduzirQuebras(int numQuebras, int seed);
    int breaks();
};

#endif
