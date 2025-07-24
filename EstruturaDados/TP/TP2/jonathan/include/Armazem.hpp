#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "Pilha.hpp"

class Armazem {
private:
    Pilha secoes[100]; // Cada secao é uma pilha de pacotes
public:
    Armazem();

    // Armazena o pacote na pilha da secao destino
    void armazenaPacote(Pacote* pacote, int secao);

    // Remove o pacote do topo da pilha da secao
    Pacote* recuperaPacote(int secao);

    // Verifica se a pilha da secao está vazia
    bool secaoVazia(int secao) const;
};



#endif