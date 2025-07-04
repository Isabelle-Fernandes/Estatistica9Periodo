#include "../include/BancoDados.hpp"

BancoDados::BancoDados(){
    this->tamanho = 0;
    this->eventos = new Evento[this->capacidade]; 
}

BancoDados::~BancoDados() {
    delete[] this->eventos;
}

void BancoDados::addEvento(const Evento &evento) {
    // Verifica se precisa de mais espaco ANTES de inserir
    if (this->tamanho == (this->capacidade - 1)) {
        redimensionar();
    }
    // Adiciona o evento ao array
    this->eventos[this->tamanho] = evento;
    this->tamanho++;
}

// redimensiona o tamanho do vetor Eventos
void BancoDados::redimensionar(){
    Evento* novoArray = new Evento[this->capacidade*2];

    // Copia todos os eventos existentes para o novo array
    for (int i = 0; i < this->tamanho; ++i) {
        novoArray[i] = this->eventos[i];
    }

    delete[] eventos;

    this->eventos = novoArray;
    this->capacidade = capacidade*2;
} 
    