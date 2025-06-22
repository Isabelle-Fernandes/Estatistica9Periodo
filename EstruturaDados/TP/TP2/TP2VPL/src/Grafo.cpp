#include "../include/Grafo.hpp"
#include <iostream>

Vertice::Vertice(int v) {
    this->vertice = v;
    this->prox = nullptr;
}

ListaAdjacencia::ListaAdjacencia(int v) {
    this->origem = new Vertice(v);
    ultimo = origem;
    grauVertice = 0;
}

ListaAdjacencia::~ListaAdjacencia() {
    Vertice* atual = origem;
    while (atual->prox != nullptr) {
        Vertice* temp = atual;
        atual = temp->prox;
        delete temp;
    }
    delete atual; 
}

void ListaAdjacencia::addAresta(int v) {
    Vertice* novoVertice = new Vertice(v);
    Vertice* atual = ultimo;
    atual->prox = novoVertice;
    ultimo = novoVertice;
    this->grauVertice++;
}


Grafo::Grafo(int n){
    numeroVertices = n;
    numeroLigacao = 0;
    listaAdjacencia = new ListaAdjacencia*[n];
    for(int i = 0; i < n; i++)
        listaAdjacencia[i] = new ListaAdjacencia(i);
}

Grafo::~Grafo() {
    for(int i = 0; i < numeroVertices; i++) {
        delete listaAdjacencia[i];
    }
    delete[] listaAdjacencia;
}

void Grafo::addAresta(int origem, int v){
    listaAdjacencia[origem]->addAresta(v);
}

void Grafo::imprimeGrafo(){
    for(int i = 0; i < numeroVertices; i++){
        Vertice* atual = listaAdjacencia[i]->origem;
        std::cout << "Vértice " << i << ": ";
        while(atual->prox != nullptr) {
            std::cout << atual->prox->vertice << " ";
            atual = atual->prox;
        }
        std::cout << std::endl;
    }
}

int Grafo::obterNumeroLigacao(){
    int _numeroLigacao = 0;
    for(int i = 0; i < this->numeroVertices; i++){
        _numeroLigacao += this->listaAdjacencia[i]->grauVertice;
    }
    return _numeroLigacao;
}
