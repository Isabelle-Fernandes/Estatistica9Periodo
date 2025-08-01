#include "Vetor.hpp"

#include "QuicksortIns.hpp"
#include "Insertion.hpp"

#include <cstdlib> 

Vetor::Vetor(const Vetor &copia){
    tam = VETSZ;
    for (int i = 0; i < tam; ++i) itens[i] = copia.itens[i];  

    chamadas = 0;
    comparacoes = 0;
    movimentacoes = 0;
}

Vetor::Vetor() {
    tam = VETSZ;
    chamadas = 0;
    comparacoes = 0;
    movimentacoes = 0;
}


void Vetor::inccalls(int num){
    this->chamadas += num;
}

void Vetor::inccmp(int num){
    this->comparacoes += num;
}

void Vetor::incmov(int num){
    this->movimentacoes += num;
}

void Vetor::InduzirQuebras(int numQuebras, int seed){
    srand48(seed);
    int p1 = 0, p2 = 0;
    Item temp;
    for (int t = 0; t < numQuebras; t++) {
    /* Gera dois índices distintos no intervalo [0..size-1] */
        while (p1 == p2) {
            p1 = (int)(drand48() * this->tam);
            p2 = (int)(drand48() * this->tam);
        }
        /* Realiza a troca para introduzir uma quebra */
        temp = this->itens[p1];
        this->itens[p1] = this->itens[p2];
        this->itens[p2] = temp;
        p1 = p2 = 0;
    }
}

int Vetor::breaks(){
    int breaks = 0;
    for(int i = 0; i < (this->tam - 1); i++){
        if(this->itens[i+1] < this->itens[i]) breaks ++;
    }
    return breaks;
}

void Vetor::resetCounter(){
    this->chamadas = 0;
    this->comparacoes = 0;
    this->movimentacoes = 0;
}