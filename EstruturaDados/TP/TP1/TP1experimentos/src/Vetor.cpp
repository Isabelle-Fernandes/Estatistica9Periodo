#include "Vetor.hpp"
#include "QuicksortIns.hpp"
#include "Insertion.hpp"

#include <cstdlib> 
#include <cmath>

Vetor::Vetor(const Vetor &copia){
    tam = VETSZ;
    for (int i = 0; i < tam; ++i) itens[i] = copia.itens[i];  

    chamadas = 0;
    comparacoes = 0;
    movimentacoes = 0;
}

Vetor::Vetor(int seed_) {
    this->tam = VETSZ;
    this->chamadas = 0;
    this->comparacoes = 0;
    this->movimentacoes = 0;

    int i, j, p;
    long mult = (long)pow(10, KEYSZ - 1);

    srand48(seed_);  // inicializa o gerador com uma semente

    for (i = 0; i < VETSZ; i++) {
        // gera uma chave aleatória e extrai cada dígito
        for (j = (int)(drand48() * mult), p = KEYSZ - 2; p >= 0; j /= 10, p--)
            this->itens[i].key[p] = '0'+ (j % 10);
        this->itens[i].key[KEYSZ - 1] = '\0';  // termina a string

        // preenche o payload com '0', '1', ..., até PLSZ-2
        for (j = 0; j < PLSZ - 1; j++)
            this->itens[i].payload[j] = '0' + (j % 10);
        this->itens[i].payload[PLSZ - 1] = '\0';
    }

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