#ifndef PACOTE_HPP
#define PACOTE_HPP

#include <string>

// Enum adicionado para maior clareza dos estados do pacote.
enum PacoteEstado {
    NAO_POSTADO,
    EM_ARMAZEM,
    EM_TRANSITO,
    ENTREGUE
};

class Pacote {
private:
    int id;
    int origem;
    int destino;
    long long tempoUltimoArmazenamento;
    long long tempoUltimoTransporte;
    long long tempoTotalArmazenado;
    long long tempoTotalTransporte;
    int rota[100];
    int tamanhoRota;
    int posicaoRota;
    PacoteEstado estado;

public:
    Pacote();
    void setId(int newId);
    int getId() const;
    void setOrigem(int newOrigem);
    int getOrigem() const;
    void setDestino(int newDestino);
    int getDestino() const;
    void setTempoUltimoArmazenamento(long long tempo);
    long long getTempoUltimoArmazenamento() const;
    void setTempoUltimoTransporte(long long tempo);
    long long getTempoUltimoTransporte() const;
    void registraTempoArmazenado(long long tempo);
    void registraTempoTransporte(long long tempo);
    int* getRota();
    void setTamanhoRota(int tam);
    int getTamanhoRota() const;
    void avancaNaRota();
    int getPosicaoRota() const;
    void setEstado(PacoteEstado st);
    PacoteEstado getEstado() const;
};

#endif