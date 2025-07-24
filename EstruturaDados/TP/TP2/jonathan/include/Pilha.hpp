#ifndef PILHA_HPP
#define PILHA_HPP

#include "Pacote.hpp"

struct Node {
    Pacote* pacote;
    Node* next;
    Node(Pacote* p) : pacote(p), next(0) {}
};

class Pilha {
private:
    Node* topo;
public:
    Pilha();
    ~Pilha();
    void push(Pacote* pacote);
    Pacote* pop();
    bool vazia() const;
};
#endif