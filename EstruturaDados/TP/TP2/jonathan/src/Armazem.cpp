#include "Armazem.hpp"

Armazem::Armazem() {}

void Armazem::armazenaPacote(Pacote* pacote, int secao) {
    secoes[secao].push(pacote);
}

Pacote* Armazem::recuperaPacote(int secao) {
    return secoes[secao].pop();
}

bool Armazem::secaoVazia(int secao) const {
    return secoes[secao].vazia();
}
