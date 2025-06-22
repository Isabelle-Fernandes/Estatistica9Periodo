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

Pacote* Pilha::retiraMaisAntigo(int &custo) {
    Pacote* resultado;

    //Caso 1: A pilha estah vazia
    if (estahVazia()) {
        return nullptr;
    }

    //Caso 2: A pilha so tem um pacote. Ele eh o mais antigo.
    if (this->tamanho == 1) {
        resultado = this->desempilha();
        custo = 1;
        return resultado;
    }

    // Caso 3: A pilha tem mais de 1 pacote.
    Pilha auxiliar;

    // Mover todos os pacotes, da pilha principal para a pilha auxiliar.
    while (this->tamanho > 0) {
        auxiliar.empilha(this->desempilha());
        custo ++; // Cada movimento tem um custo
    }

    // Remove o pacote do topo da pilha auxiliar
    resultado = auxiliar.desempilha();

    while (!auxiliar.estahVazia()) {
        this->empilha(auxiliar.desempilha());
    }
   
    return resultado;
}