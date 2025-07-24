#include "Escalonador.hpp"

Escalonador::Escalonador() {}

void Escalonador::inicializa() {}

void Escalonador::insereEvento(const Evento& e) {
    filaEventos.insere(e);
}

Evento Escalonador::proximoEvento() {
    return filaEventos.retira();
}

bool Escalonador::haEventos() const {
    return !filaEventos.vazio();
}
