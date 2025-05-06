#ifndef GRAPH_HPP
#define GRAPH_HPP

class TipoCelula{
    
    public:
        TipoCelula();
        TipoCelula(int v);
        int vertice;
        TipoCelula *prox;
            
};

class ListaAdjacencia{

    public:
        ListaAdjacencia(int numVertices);
        ~ListaAdjacencia();
        bool VerificaListaVazia(int v);
        void Insere(int v, int u);
        void Imprime(int v);
        int  QuantidadeVizinhosVertice(int v);
        int QuantidadeArestasLista();
        bool EhgrafoCompleto();
        TipoCelula** lista;
        int tamanhoLista;

};

class Grafo{
    
    public:
        Grafo(int numVertices);
        ~Grafo();
        void InsereVertice();
        void InsereAresta(int v, int u);
        int QuantidadeVertices();
        int QuantidadeArestas();
        int GrauMinimo();
        int GrauMaximo();
        void ImprimeVizinhos(int v);
    
    private:
        ListaAdjacencia vertices;

};

class Menu{
    
    public:
        Grafo criaGrafo();
        void ImprimeDadoBasico(Grafo *grafo);
        void ImprimeVizinhos(Grafo *grafo);
        //void GrafoCompleto(Grafo *grafo);
    
};

#endif
