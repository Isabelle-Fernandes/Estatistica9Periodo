// Fila.hpp
#ifndef FILA_HPP
#define FILA_HPP

#include <iostream> 
#include <cstdlib> 

template <typename T>
class NoFila {
public:
    T item;           
    NoFila<T>* prox;  

    NoFila(T i) {
        item = i;
        prox = nullptr;
    }
};

template <typename T>
class Fila {
public:
    NoFila<T>* primeiro;
    NoFila<T>* ultimo;

    Fila() {
        primeiro = nullptr;
        ultimo = nullptr;
    }

    ~Fila() {
        while (!estahVazia()) {
            desenfileira();
        }
    }

    bool estahVazia() {
        return (primeiro == nullptr);
    }

    // Adicionar um item no fim da fila
    void enfileira(T item) { 
        NoFila<T>* novoNo = new NoFila<T>(item);

        if (estahVazia()) {
            // Se a fila esta vazia, o novo no eh tanto o inicio quanto o fim
            primeiro = novoNo;
            ultimo = novoNo;
        } else {
            ultimo->prox = novoNo;
            // o novo no se torna o ultimo
            ultimo = novoNo;
        }
    }

    // Remover e retornar o item do inicio da fila
    T desenfileira() {
        if (estahVazia()) {
            std::cerr << "ERRO: Tentativa de desenfileirar de uma fila vazia!" << std::endl;
            exit(1); 
        }

        // Guarda o no da frente para poder libera-lo depois
        NoFila<T>* noRemovido = primeiro;
        T itemRemovido = noRemovido->item; 

        // Avanca o ponteiro frente para o proximo no
        primeiro = primeiro->prox;

        // Se, apos a remocao, a fila ficou vazia, o ponteiro 'ultimo' tambem deve ser null
        if (primeiro == nullptr) {
            ultimo = nullptr;
        }

        delete noRemovido;

        return itemRemovido;
    }
};

#endif