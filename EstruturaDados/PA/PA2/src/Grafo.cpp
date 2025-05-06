# include "Grafo.hpp"
#include <iostream>
#include <sstream>

TipoCelula::TipoCelula() : vertice(-1), prox(nullptr) {}

TipoCelula::TipoCelula(int v) : vertice(v), prox(nullptr) {}

ListaAdjacencia::ListaAdjacencia(int numVertices){
    this->tamanhoLista = numVertices;
    this->lista = new TipoCelula*[numVertices];
    
    for(int i = 0; i < numVertices; i++){
        this->lista[i] = nullptr;
    }
}

ListaAdjacencia::~ListaAdjacencia(){
    for(int i = 0; i < this->tamanhoLista; i++){
        TipoCelula *atual = this->lista[i];
        while(atual != nullptr){
            TipoCelula *temp = atual;
            atual = atual->prox;;
            delete temp;
        }
    }
    delete[] lista;
}

bool ListaAdjacencia:: VerificaListaVazia(int v){
    return this->lista[v] == nullptr;
} 

void ListaAdjacencia::Insere(int v, int u){
    TipoCelula *nova = new TipoCelula(u);
    if(this->VerificaListaVazia(v))
        this->lista[v] = nova;
    else {
        TipoCelula *atual = this->lista[v];
        while(atual->prox != nullptr)
            atual = atual->prox;
        atual->prox = nova;
    }
}

void ListaAdjacencia::Imprime(int v){
    if(this->VerificaListaVazia(v)){
        std::cout << " " << std::endl;
    } else {
        TipoCelula *atual = this->lista[v];
        while(atual != nullptr){
            std::cout << atual->vertice << " ";
            atual = atual->prox;
        }
    } 
    std::cout << std::endl;
}

int ListaAdjacencia::QuantidadeVizinhosVertice(int v){
    int quantidade = 0;
    if(VerificaListaVazia(v))
        return quantidade; 
    
    TipoCelula *atual = this->lista[v];
        while(atual != nullptr){
            atual = atual->prox;
            quantidade++;
        }
    return quantidade;
}

int ListaAdjacencia::QuantidadeArestasLista(){
    int quantidade = 0;
    for(int i = 0; i < this->tamanhoLista; i++)
        quantidade += this->QuantidadeVizinhosVertice(i);
    return quantidade/2;
}

bool ListaAdjacencia::EhgrafoCompleto(){
    int quantidadeGrafoCompleto = (this->tamanhoLista * (this->tamanhoLista - 1)) / 2;
    return this->QuantidadeArestasLista() == quantidadeGrafoCompleto;
}

Grafo::Grafo(int numVertices) : vertices(ListaAdjacencia(numVertices)) {}

Grafo::~Grafo() {}

void Grafo::InsereVertice(){}

void Grafo::InsereAresta(int v, int u){
    this->vertices.Insere(v, u);
}

int Grafo::QuantidadeVertices(){
    return this->vertices.tamanhoLista;
}

int Grafo::QuantidadeArestas(){
    return this->vertices.QuantidadeArestasLista();
}

int Grafo::GrauMinimo(){
    int grauMinimo = this->vertices.QuantidadeVizinhosVertice(0);
    for(int i = 1; i < this->vertices.tamanhoLista; i++){
        int grau = this->vertices.QuantidadeVizinhosVertice(i);
        if(grau < grauMinimo)
            grauMinimo = grau;
    }
    return grauMinimo;
}

int Grafo::GrauMaximo(){
    int grauMaximo = this->vertices.QuantidadeVizinhosVertice(0);
    for(int i = 1; i < this->vertices.tamanhoLista; i++){
        int grau = this->vertices.QuantidadeVizinhosVertice(i);
        if(grau > grauMaximo)
            grauMaximo = grau;
    }
    return grauMaximo;
}

void Grafo::ImprimeVizinhos(int v){
    this->vertices.Imprime(v);
}

Grafo Menu::criaGrafo(){
    int numVertices;
    std::cin >> numVertices;

    std::cin.ignore();

    Grafo grafo = Grafo(numVertices);

    for(int vertice = 0; vertice < numVertices; vertice++) {
        int numVizinho;
        std::string linha;

        std::getline(std::cin, linha);
        
        std::istringstream iss(linha);

        iss >> numVizinho;

        for(int i = 0; i < numVizinho; i++) {
            int verticeVizinho;
            iss >> verticeVizinho;
            grafo.InsereAresta(vertice, verticeVizinho);
        }
    }

    return grafo;

}

void Menu::ImprimeDadoBasico(Grafo *grafo){
    std::cout << grafo->QuantidadeVertices() << std::endl;
    std::cout << grafo->QuantidadeArestas() << std::endl;
    std::cout << grafo->GrauMinimo() << std::endl;
    std::cout << grafo->GrauMaximo() << std::endl;
}

void Menu::ImprimeVizinhos(Grafo *grafo){
    int numVertices = grafo->QuantidadeVertices();
    for(int i = 0; i < numVertices; i++){
        grafo->ImprimeVizinhos(i);
    }
}

/*void Menu::GrafoCompleto(Grafo *grafo){
    std::cout << grafo->vertices.EhgrafoCompleto() << std::endl;
}*/


