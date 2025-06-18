#ifndef CALCULAROTA_HPP
#define CALCULAROTA_HPP

#include "Grafo.hpp"
#include "Fila.hpp"
#include "Pacote.hpp"
#include <iostream>

void ImprimeRota(int* rota, int tamanho_rota);

int* BuscaMenorRota(Pacote &pacote, Grafo &grafo);

#endif