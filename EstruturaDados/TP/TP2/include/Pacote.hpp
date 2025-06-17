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
    void Inicializar(int tempo, char * _remetente, char * _destinatario, int _tipo, int _armazemOrigem, int _armazemDestino);
    int tempoAtual;
    char* nomeRemetente;
    char* nomeDestinatario;
    int tipo;
    int armazemOrigem;
    int armazemDestino;
    int estadoPacote;
    //Estatistica * estatisticas;
    int* rota;
    int tamanhoRota;
    int proximoDestino;
    int getProximoDestinoNaRota();
};

char* lerPalavraDinamica(std::ifstream& arquivo);

#endif