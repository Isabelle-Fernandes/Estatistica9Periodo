
#ifndef GRAFO_HPP
#define GRAFO_HPP

class Vertice{
public:
    int vertice;
    Vertice(int v);
    Vertice* prox;
};

class ListaAdjacencia {
public:
    Vertice* origem;
    Vertice* ultimo;
    int grauVertice;
    ListaAdjacencia(int v);
    ~ListaAdjacencia();
    void addAresta(int vertice); //nessa funcao, ja incremento tambem o grau do vertice
};

class Grafo{
public:
    int numeroVertices;
    int numeroLigacao; // dado importante para escalonar evento transporte
    ListaAdjacencia** listaAdjacencia;
    Grafo(int n);
    ~Grafo();
    void addAresta(int origem, int v);
    void imprimeGrafo();
    int obterNumeroLigacao();
};


#endif

