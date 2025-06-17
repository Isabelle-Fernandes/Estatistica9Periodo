#ifndef PACOTE_HPP
#define PACOTE_HPP

//#include "Estatistica.hpp"
#include <fstream>
#include <cstring>


// aqui estao os estados do pacote
#define naoPostado 1
#define chegadaEscalonadaArmazem 2
#define chegouAguardaArmazem 3
#define armazenado 4
#define alocadoTransporte 5
#define entregue 6

class Pacote {
public:
    ~Pacote();
    void Inicializar(int tempo, int id, int _armazemOrigem, int _armazemDestino);
    int tempoAtual;
    int id;
    int armazemOrigem;
    int armazemDestino;
    int estadoPacote;
    //Estatistica * estatisticas;
    int* rota;
    int tamanhoRota;
    int proximoDestino;
    int getProximoDestinoNaRota();
};

#endif