#include "Pacote.hpp"

Pacote::Pacote() {
    id = -1;
    origem = -1;
    destino = -1;
    tempoUltimoArmazenamento = 0;
    tempoUltimoTransporte = 0;
    tempoTotalArmazenado = 0;
    tempoTotalTransporte = 0;
    tamanhoRota = 0;
    posicaoRota = 0;
    estado = NAO_POSTADO;
}

void Pacote::setId(int newId) { id = newId; }
int Pacote::getId() const { return id; }

void Pacote::setOrigem(int newOrigem) { origem = newOrigem; }
int Pacote::getOrigem() const { return origem; }

void Pacote::setDestino(int newDestino) { destino = newDestino; }
int Pacote::getDestino() const { return destino; }

void Pacote::setTempoUltimoArmazenamento(long long tempo) { tempoUltimoArmazenamento = tempo; }
long long Pacote::getTempoUltimoArmazenamento() const { return tempoUltimoArmazenamento; }

void Pacote::setTempoUltimoTransporte(long long tempo) { tempoUltimoTransporte = tempo; }
long long Pacote::getTempoUltimoTransporte() const { return tempoUltimoTransporte; }

void Pacote::registraTempoArmazenado(long long tempo) { tempoTotalArmazenado += tempo; }
void Pacote::registraTempoTransporte(long long tempo) { tempoTotalTransporte += tempo; }

int* Pacote::getRota() { return rota; }
void Pacote::setTamanhoRota(int tam) { tamanhoRota = tam; }
int Pacote::getTamanhoRota() const { return tamanhoRota; }

void Pacote::avancaNaRota() { if(posicaoRota < tamanhoRota - 1) posicaoRota++; }
int Pacote::getPosicaoRota() const { return posicaoRota; }

void Pacote::setEstado(PacoteEstado st) { estado = st; }
PacoteEstado Pacote::getEstado() const { return estado; }