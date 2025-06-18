#include "../include/Fila.hpp"

NoFila::NoFila(int i) {
    item = i;
    prox = nullptr;
}

Fila::Fila() {
    primeiro = nullptr;
    ultimo = nullptr;
}

Fila::~Fila() {
    while (!estahVazia()) {
        desenfileira();
    }
}

bool Fila::estahVazia() { // verifica se a fila esta vazia
    return (primeiro == nullptr);
}

void Fila::enfileira(int item) {
    NoFila* novoNo = new NoFila(item);

    if (estahVazia()) {
        // Se a fila estah vazia, o novo no eh tanto o inicio quanto o fim
        primeiro = novoNo;
        ultimo = novoNo;
    } else {
        // Se ja ha elementos, o ultimo item da fila aponta para o novo no...
        ultimo->prox = novoNo;
        // o novo no se torna o ultimo
        ultimo = novoNo;
    }
}

// Remove e retorna o item do inicio da fila (da "frente")
int Fila::desenfileira() {
    if (estahVazia()) {
        std::cerr << "ERRO: Tentativa de desenfileirar de uma fila vazia!" << std::endl;
        exit(1); 
    }

    // Guarda o no da frente para poder libera-lo depois
    NoFila* noRemovido = primeiro;
    int itemRemovido = noRemovido->item;

    // Avanca o ponteiro frente para o proximo no
    primeiro = primeiro->prox;

    // Se, apos a remocao, a fila ficou vazia, o ponteiro 'ultimo' tambem deve ser null
    if (primeiro == nullptr) {
        ultimo = nullptr;
    }

    delete noRemovido;

    return itemRemovido;
}