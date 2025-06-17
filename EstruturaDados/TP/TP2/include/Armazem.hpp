#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "Pilha.hpp" 
#include "Pacote.hpp"

// Uma estrutura para retornar os pacotes recuperados para transporte e o custo da operacao
struct ResultadoTransporte {
    Pilha pacotes; // Uma nova pilha contendo os pacotes a serem transportados
    int custoTotalManipulacao;
};

class Armazem {
public:
    int id;                   // O ID deste armazem (ex: 0, 1, 2...)
    int grau;                 // O numero de secoes deste armazem
    Pilha* secoes;            // Array de pilhas (as secoes LIFO)
    int* mapaDeDestinos;      // Array que mapeia: secao[i] e para destino mapaDeDestinos[i]

    // Funcao auxiliar para encontrar o indice da secao para um dado destino
    int encontraIndiceDaSecao(int idDestino);

    Armazem();
    ~Armazem();

    // Inicializa o armazem com seu ID e suas conexoes (vizinhos)
    void inicializar(int idArmazem, int grauDoVertice, int* idsDosVizinhos);

    // A funcao descobre o proximo destino na rota do pacote e o coloca na pilha certa.
    void armazena(Pacote* p);

    // Recupera os pacotes mais antigos da secao que vai para 'idDestino', ate o limite da 'capacidade'.
    ResultadoTransporte recuperaParaTransporte(int idDestino, int capacidade);
    
    // Verifica se o armazem esta completamente vazio.
    bool estahVazio();
};

#endif