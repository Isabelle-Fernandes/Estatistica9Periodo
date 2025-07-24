#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "Evento.hpp"
#include "MinHeap.hpp"

class Escalonador {
private:
    MinHeap filaEventos;
public:
    Escalonador();
    void inicializa();
    void insereEvento(const Evento& e);
    Evento proximoEvento();
    bool haEventos() const;
};

#endif
