#ifndef PILHA_HPP
#define PILHA_HPP

#include "Pacote.hpp"

struct ResultadoRetirada { // Estrutura para retornar o resultado da operacao de retirada
    Pacote* pacote;
    int custoManipulacao; // Numero de movimentos de pacotes
};

class Item {
public:
    Pacote* pacote;
    Item* prox;
    Item(Pacote* p);
};

class Pilha {
public:
    Item* topo;
    int tamanho;
    Pilha();
    ~Pilha();
    void empilha(Pacote* p);
    Pacote* desempilha();
    bool estahVazia();
    ResultadoRetirada retiraMaisAntigo();
};
    

#endif