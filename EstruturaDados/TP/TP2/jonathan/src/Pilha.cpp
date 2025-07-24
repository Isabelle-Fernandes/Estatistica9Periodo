#include "Pilha.hpp"

Pilha::Pilha() {
    topo = 0;
}

Pilha::~Pilha() {
    while (!vazia()) pop();
}

void Pilha::push(Pacote* pacote) {
    Node* novo = new Node(pacote);
    novo->next = topo;
    topo = novo;
}

Pacote* Pilha::pop() {
    if (vazia()) return 0;
    Node* temp = topo;
    Pacote* pacote = temp->pacote;
    topo = topo->next;
    delete temp;
    return pacote;  
}

bool Pilha::vazia() const {
    return topo == 0;
}
