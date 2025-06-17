#ifndef FILA_HPP
#define FILA_HPP

#include <iostream>

class NoFila {
public:
    int item;
    NoFila* prox;
    NoFila(int i);
};

class Fila {
public:
    NoFila* primeiro; 
    NoFila* ultimo;  
    Fila();   
    ~Fila(); 
    void enfileira(int item);  // Adiciona um item no fim da fila
    int desenfileira(); // Remove e retorna o item do inicio da fila
    bool estahVazia();  // Verifica se a fila esta vazia

};

#endif

