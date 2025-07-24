#ifndef SIMULADOR_HPP
#define SIMULADOR_HPP

#include "Pacote.hpp"
#include "Armazem.hpp"
#include "Escalonador.hpp"
#include "Evento.hpp"
#include "Pilha.hpp"

class Simulador {
private:
    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransportes;
    int custoRemocao;
    int numeroArmazens;
    int totalPacotes; // Adicionado para condição de parada
    int grafo[100][100];
    Pacote* pacotesPorId[10000];
    Armazem armazens[100];
    Escalonador escalonador;

public:
    Simulador();
    ~Simulador();

    void lerEntrada(const char* nomeArquivo);
    void rodarSimulacao();

private:
    void calcularRota(Pacote& pacote);
    void bfs(int origem, int destino, int rota[], int& tamanho);
    // Alterado: recebe o tempo inicial para o primeiro agendamento
    void agendarTransportes(long long tempoInicial);
};

#endif