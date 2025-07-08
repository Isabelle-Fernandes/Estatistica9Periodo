// Fila.hpp
#ifndef FILA_HPP
#define FILA_HPP

#include <iostream> 
#include <cstdlib> 

template <typename T>
class NoFila {
public:
    T indice;           
    NoFila<T>* prox;  

    NoFila(T i) {
        indice = i;
        prox = nullptr;
    }
};

template <typename T>
class Fila {
public:
    NoFila<T>* primeiro;
    NoFila<T>* ultimo;
    int tamanho;

    Fila() {
        primeiro = nullptr;
        ultimo = nullptr;
        tamanho = 0;
    }

    ~Fila() {
        while (!estahVazia()) {
            deletarFila();
        }
    }

    bool estahVazia() {
        return (primeiro == nullptr);
    }

    // Adicionar um indice no fim da fila
    void enfileira(T indice) { 
        NoFila<T>* novoNo = new NoFila<T>(indice);

        if (estahVazia()) {
            // Se a fila esta vazia, o novo no eh tanto o inicio quanto o fim
            primeiro = novoNo;
            ultimo = novoNo;
        } else {
            ultimo->prox = novoNo;
            // o novo no se torna o ultimo
            ultimo = novoNo;
        }
        this->tamanho++;
    }

    void deletarFila() {
        if (estahVazia()) {
            std::cerr << "ERRO: Tentativa de desenfileirar de uma fila vazia!" << std::endl;
            exit(1); 
        }

        // Guarda o no da frente para poder libera-lo depois
        NoFila<T>* noRemovido = primeiro;

        // Avanca o ponteiro frente para o proximo no
        primeiro = primeiro->prox;

        // Se, apos a remocao, a fila ficou vazia, o ponteiro 'ultimo' tambem deve ser null
        if (primeiro == nullptr) {
            ultimo = nullptr;
        }
        delete noRemovido;
    }

};


#endif