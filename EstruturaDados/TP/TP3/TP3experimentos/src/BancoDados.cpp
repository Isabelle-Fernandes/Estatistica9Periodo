#include "../include/BancoDados.hpp"

// Construtor aloca um array de PONTEIROS
BancoDados::BancoDados() {
    this->capacidade = 100;
    this->tamanho = 0;
    this->eventos = new Evento*[this->capacidade]; // MUDANCA: new Evento*[...]
}

BancoDados::~BancoDados() {
    // Deleta cada objeto ponteiro Evento individualmente
    for (int i = 0; i < this->tamanho; i++) {
        delete this->eventos[i];
    }
    // Deleta o array de ponteiros
    delete[] this->eventos;
}

// addEvento cria um novo Evento na heap
void BancoDados::addEvento(const Evento& evento) {
    if (this->tamanho == this->capacidade) {
        redimensionar();
    }
    // Cria uma copia do evento na HEAP e guarda o PONTEIRO no array
    this->eventos[this->tamanho] = new Evento(evento);
    this->tamanho++;
}

// redimensionar copia ponteiros
void BancoDados::redimensionar() {
    int novaCapacidade = this->capacidade * 2;
    Evento** novoArray = new Evento*[novaCapacidade];

    // Copia os PONTEIROS
    for (int i = 0; i < this->tamanho; ++i) {
        novoArray[i] = this->eventos[i];
    }

    delete[] this->eventos; // Deleta apenas o array antigo de ponteiros

    this->eventos = novoArray;
    this->capacidade = novaCapacidade;
}
    