#ifndef PACOTE_HPP
#define PACOTE_HPP

//#include "Estatistica.hpp"
#include <cstring>


// aqui estao os estados do pacote
#define naoPostado 1
#define chegadaEscalonadaArmazem 2
#define armazenado 3
#define alocadoTransporte 4
#define entregue 5

class Pacote {
public:
    ~Pacote();
    void Inicializar(int tempo, int _id, int _armazemOrigem, int _armazemDestino);
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
    void imprimePacote();
};

#endif