#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "Pilha.hpp" 
#include "Pacote.hpp"
#include "Grafo.hpp"

class Armazem {
public:
    int id; // O ID do armazem (ex: 0, 1, 2...)
    int grau; // O numero de secoes deste armazem, que eh a quantidade de vertices ligado a ele
    Pilha* secoes; // Array de pilhas (as secoes LIFO)
    int* mapaDeDestinos; // Array que mapeia: secao[i] e para destino mapaDeDestinos[i]
    int custoDesempilha;

    // Funcao auxiliar para encontrar o indice da secao para um dado destino
    int encontraIndiceDaSecao(int idDestino);

    Armazem();
    ~Armazem();

    // Inicializa o armazem com seu ID e suas conexoes (vizinhos)
    void inicializar(int idArmazem, Grafo* grafo, int custo);

    // A funcao descobre o proximo destino na rota do pacote e o coloca na pilha certa.
    void armazena(Pacote* p, int _tempoAtual);

    // Recupera os pacotes mais antigos da secao que vai para idDestino, ate o limite da capacidade e computa o custo de desempilhar
    // Fila<Pacote> recuperaParaTransporte(int idDestino, int capacidade, int tempoRelogio);

    void desempilhaSecao(int idDestino, Pilha& pilhaDeSaida);
        
    // Verifica se determinada secao do armazem estah vazia
    bool secaoVazia(int s);

    // Verifica se o armazem esta completamente vazio.
    bool armazemVazio();

};

bool verificaTodosArmazensVazios(int qtdeArmazem, Armazem* armazem); // funcao que verifica se todos os armazens estao vazios

#endif