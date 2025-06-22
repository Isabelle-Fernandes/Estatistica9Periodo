#include "../include/Evento.hpp"
#include <iostream>

Evento::Evento(){
    tempoEscalonado = -1;
    tipo = NAOINICIALIZADO;
    pacote = nullptr;
    IdArmazens[0] = -1;
    IdArmazens[1] = -1;
    chavePrioridade = -1;
}

Evento::Evento(int _tempoEscalonado, int IdArmazemOrigem, int IdArmazemDestino){ // esse eh o evento transporte
    tempoEscalonado = _tempoEscalonado;
    pacote = nullptr;
    tipo = TRANSPORTE;
    IdArmazens[0] = IdArmazemOrigem; // aqui estou convencionando que no array posicao 0 eh armazem origem
    IdArmazens[1] = IdArmazemDestino; // aqui estou convencionando que no array posicao 1 eh armazem destino
    chavePrioridade = calculaChave(TRANSPORTE);
} 

Evento::Evento(int _tempoEscalonado, Pacote* _pacote, int _armazemDeChegada){ // esse eh o evento pacote chegou em algum armazem
    tempoEscalonado = _tempoEscalonado;
    tipo = PACOTE;
    pacote = _pacote;
    IdArmazens[0] = _armazemDeChegada; // aqui estou convencionando que no array posicao 0 eh armazem origem
    IdArmazens[1] = -1; // nao eh preciso saber o armazem de destino
    chavePrioridade = calculaChave(PACOTE);
        
}

long long Evento::calculaChave(TipoEvento _tipo){
    if(_tipo == PACOTE){
        long long chave;
        long long tipo = _tipo;
        long long pacote = this->pacote->id * 10;
        long long tempo = (long long)this->tempoEscalonado * 10000000LL;
        chave = tipo + pacote + tempo;
        return chave;
    }

    // cria chave para evento tipo TRANSPORTE
    long long chave;
    long long tipo = _tipo;
    long long destino = this->IdArmazens[1] * 10;
    long long origem = this->IdArmazens[0] * 10000;
    long long tempo = (long long)this->tempoEscalonado * 10000000LL;
    chave = tipo + destino + origem + tempo;
    return chave;
}

void Evento::imprimeEvento(){
    if(this->tipo == PACOTE) {
        std::cout << this -> pacote->tempoAtual
        << " pacote " 
        << pacote->id
        << " armazenado em "
        << pacote->armazemAtual 
        << " na secao "
        << pacote->getProximoDestinoNaRota() << std::endl;

    } else {
        std::cout << this -> pacote->tempoAtual
        << " pacote " 
        << pacote->id
        << " em transito de "
        << pacote->armazemAtual 
        << " para "
        << pacote->getProximoDestinoNaRota() << std::endl;
    }
}

bool Evento::operator<(const Evento& outro) const {
    return chavePrioridade < outro.chavePrioridade;
}

bool Evento::operator>(const Evento& outro) const {
    return chavePrioridade > outro.chavePrioridade;
}

bool Evento::operator==(const Evento& outro) const {
    return chavePrioridade == outro.chavePrioridade;
}

