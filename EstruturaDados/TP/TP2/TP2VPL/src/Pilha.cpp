#include "../include/Pilha.hpp"

NoPilha::NoPilha(Pacote* p){
    pacote = p;
    prox = nullptr;
}

Pilha::Pilha() {
    topo = nullptr;
    tamanho = 0;
}

Pilha::~Pilha() {
    while (!estahVazia()) {
        desempilha();
    }
}

bool Pilha::estahVazia() {
    return (topo == nullptr);
}


void Pilha::empilha(Pacote* p) {
    NoPilha* novoItem = new NoPilha(p);
    novoItem->prox = topo; // O novo no aponta para o antigo topo
    topo = novoItem;       // O novo no se torna o topo
    tamanho++;
}

Pacote* Pilha::desempilha() {
    if (estahVazia()) {
        return nullptr; 
    }

    NoPilha* itemRemovido = topo;
    Pacote* pacoteRemovido = itemRemovido->pacote;

    topo = topo->prox; // O topo agora e o proximo elemento
    
    delete itemRemovido;
    tamanho--;

    return pacoteRemovido;
}
