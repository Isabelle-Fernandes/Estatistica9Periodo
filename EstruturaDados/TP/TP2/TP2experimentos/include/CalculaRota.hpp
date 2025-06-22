#ifndef CALCULAROTA_HPP
#define CALCULAROTA_HPP

#include "Grafo.hpp"
#include "Pacote.hpp"

void ImprimeRota(int* rota, int tamanho_rota);

int* BuscaMenorRota(Pacote &pacote, Grafo &grafo);

#endif