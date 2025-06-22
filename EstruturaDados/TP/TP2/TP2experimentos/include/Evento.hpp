#ifndef EVENTO_HPP
#define EVENTO_HPP

#include "Pacote.hpp"

enum TipoEvento {
    TRANSPORTE, // Um caminhao transporta pacotes
    PACOTE, // chegada de pacote
    NAOINICIALIZADO // usado apenas para constructor defaul de Evento()
};

class Evento {
public:
    int tempoEscalonado;
    TipoEvento tipo;
    long long chavePrioridade;
    Pacote* pacote;
    int IdArmazens[2]; // vetor com ID armazem origem posicao 0 e ID armazem destino posicao 1    
    Evento();
    Evento(int _tempoEscalonado, int IdArmazemOrigem, int IdArmazemDestino); // Evento tipo transporte
    Evento(int _tempoEscalonado, Pacote* _pacote, int _armazemDeChegada); // Evento tipo chegada pacote

    
    long long calculaChave(TipoEvento _tipo); 
    void imprimeEvento();
    bool operator<(const Evento& outro) const;   
    bool operator>(const Evento& outro) const;
    bool operator==(const Evento& outro) const;

};


#endif