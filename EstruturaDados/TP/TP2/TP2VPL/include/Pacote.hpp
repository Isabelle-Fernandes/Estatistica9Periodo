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
#define rearmazenado 6


class Pacote {
public:
    ~Pacote();
    void Inicializar(int tempo, int _id, int _armazemOrigem, int _armazemDestino);
    int tempoAtual;
    int id;
    int armazemOrigem;
    int armazemDestino;
    int armazemAtual;
    int estadoPacote;
    //Estatistica * estatisticas;
    int* rota;
    int tamanhoRota;
    int getProximoDestinoNaRota();
    void imprimePacote();
};

int obterTempoPrimeiroPacotePostado(Pacote* pacote, int qtdePacotes);

#endif