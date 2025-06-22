#include "../include/Escalonador.hpp"

Escalonador::Escalonador(int _capacidade, int _intervaloTransporte){
    quantidadeEventos = 0;
    capacidade = _capacidade;
    eventos = new Evento[capacidade];
    intervaloTransporte = _intervaloTransporte;
}

Escalonador::~Escalonador() {
    delete[] eventos;
}

int Escalonador::GetAncestral(int i){
    return (i-1)/2;
}

int Escalonador::GetSucessorEsq(int i){
    return 2 * i + 1;
}

int Escalonador::GetSucessorDir(int i){
    return 2 * i + 2;
}

int Escalonador::GetMenorSucessor(int i){
    int esq = GetSucessorEsq(i);
    int dir = GetSucessorDir(i);


    if (esq >= quantidadeEventos) return esq;
    if (dir >= quantidadeEventos) return esq;
    
    Evento eventos_dir = this->eventos[dir];
    Evento eventos_esq = this->eventos[esq];

    if (eventos_dir < eventos_esq) return dir;
    
    return esq;
}

void Escalonador::insereEvento(Evento e){

    if(quantidadeEventos == capacidade) redimensionar(capacidade * 2);

    eventos[quantidadeEventos] = e;
    int i = quantidadeEventos;
    int p = GetAncestral(i);
    while(eventos[i] < eventos[p]){
        Evento temp = eventos[i];
        eventos[i] = eventos[p];
        eventos[p] = temp;    
        i = p;
        p = GetAncestral(i);
    }
    quantidadeEventos++;
}

Evento Escalonador::retiraProximoEvento(){
    Evento e = eventos[0];
    eventos[0] = eventos[quantidadeEventos-1];
    quantidadeEventos--;
    Conserta();

    // Reduzir a capacidade se estiver muito vazia (para economia de memória)
    if (quantidadeEventos > 0 && quantidadeEventos < capacidade / 4 && capacidade > 10)
        redimensionar(capacidade / 2);

    return e;
}

void Escalonador::Conserta(){
    int i = 0;
    int s = GetMenorSucessor(i);
    while (s < quantidadeEventos && eventos[i] > eventos[s]){
        Evento temp = eventos[s];
        eventos[s] = eventos[i];
        eventos[i] = temp;
        i = s;
        s = GetMenorSucessor(i);
    }
}

void Escalonador::redimensionar(int novaCapacidade) {
    Evento* novoArray = new Evento[novaCapacidade];

    // Copia todos os eventos existentes para o novo array
    for (int i = 0; i < quantidadeEventos; ++i) {
        novoArray[i] = eventos[i];
    }

    delete[] eventos;

    eventos = novoArray;
    capacidade = novaCapacidade;
}


bool Escalonador::heapVazio(){
    if(this->quantidadeEventos == 0)
        return true;
    return false;
}

        
