#include "../include/Armazem.hpp"

Armazem::Armazem() {
    id = -1;
    grau = -1;
    secoes = nullptr;
    mapaDeDestinos = nullptr;
}

Armazem::~Armazem() {
    delete[] secoes;
    delete[] mapaDeDestinos;
}

// Configura o armazem com base na topologia do grafo
void Armazem::inicializar(int idArmazem, Grafo* grafo, int custo) {
    this->id = idArmazem;
    this->grau = grafo->listaAdjacencia[idArmazem]->grauVertice;
    this->custoDesempilha = custo;
    
    // Aloca memoria para o array de secoes (pilhas) e para o mapa de destinos
    if (this->grau > 0) {
        this->secoes = new Pilha[this->grau];
        this->mapaDeDestinos = new int[this->grau];

        Vertice* idVizinho = grafo->listaAdjacencia[idArmazem]->origem->prox; // Pega o primeiro vizinho
        
        // Preenche o mapa de destinos com os IDs dos vizinhos
        for (int i = 0; i < this->grau; i++) {
            this->mapaDeDestinos[i] = idVizinho->vertice;
            // Avanca para o proximo vizinho
            idVizinho = idVizinho->prox;
        }

    }
}

// Funcao auxiliar para encontrar o indice da pilha correta
int Armazem::encontraIndiceDaSecao(int idDestino) {
    for (int i = 0; i < this->grau; i++) {
        if (this->mapaDeDestinos[i] == idDestino) {
            return i;
        }
    }
    return -1; // Retorna -1 se nao ha uma conexao direta
}

// Coloca um pacote na secao (pilha) correta
void Armazem::armazena(Pacote* p, int _tempoAtual) {

    p->armazemAtual = this->id;

    int proximoDestino = p->getProximoDestinoNaRota(); 
    int indiceSecao = encontraIndiceDaSecao(proximoDestino);

    this->secoes[indiceSecao].empilha(p);
    //p->tempoAtual = _tempoAtual;
    

}


void Armazem::desempilhaSecao(int idDestino, Pilha& pilhaDeSaida) {
    int indiceSecao = encontraIndiceDaSecao(idDestino);
    if (indiceSecao == -1) {
        return; // Nao faz nada se a secao nao existe.
    }

    // Transfere a posse dos nos da pilha da secao para a 'pilhaDeSaida'
    while (!this->secoes[indiceSecao].estahVazia()) {
        pilhaDeSaida.empilha(this->secoes[indiceSecao].desempilha());
    }
}

// Verifica se determinada secao do armazem esta vazia
bool Armazem::secaoVazia(int s){
    int indiceSecao = encontraIndiceDaSecao(s);
    if(!this->secoes[indiceSecao].estahVazia())
        return false;
    return true;
}

// Verifica se todas as secoes do armazem estao vazias
bool Armazem::armazemVazio() {
    for (int i = 0; i < this->grau; i++) {
        if (!this->secoes[i].estahVazia()) 
            return false; // Encontrou uma secao com pacotes, entao o armazem nao esta vazio
    }
    return true; // Se o laco terminar, todas as secoes estao vazias
}

// funcao retorna true se todos armazens estao vazios
bool verificaTodosArmazensVazios(int qtdeArmazem, Armazem* armazem){
    for (int i = 0; i < qtdeArmazem; i++) {
        if(!armazem[i].armazemVazio()) return false;    
    }
    return true;
} 


