#ifndef LISTA_PACOTES_CLIENTE_HPP
#define LISTA_PACOTES_CLIENTE_HPP

#include "Evento.hpp"

// O no da lista encadeada
class NoListaPacote {
public:
    Evento* evento;
    int id_pacote;   
    int tempo;
    long chave;
    NoListaPacote* prox;

    NoListaPacote(Evento* evento_);

    char* getTipoEvento();
};

// lista encadeada ordenada
class ListaPacotesCliente {
public:
    ListaPacotesCliente();
    ListaPacotesCliente(Evento* evento_);
    ~ListaPacotesCliente();
    void insereOrdenado(Evento* evento_);
    void atualiza(Evento* evento_);
    void imprimeResultados(int tempoConsulta) const;

private:
    NoListaPacote* cabeca;
    void remove(Evento *evento_);
};

#endif