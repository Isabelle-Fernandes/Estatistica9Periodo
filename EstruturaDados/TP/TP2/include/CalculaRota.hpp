#ifndef CALCULAROTA_HPP
#define CALCULAROTA_HPP

#include "Grafo.hpp"
#include "Fila.hpp"
#include "Pacote.hpp"
#include <iostream>

void ImprimeRota(int* rota, int tamanho_rotanho);

int* BuscaMenorRota(Pacote &pacote, Grafo &grafo, int &tamanho_rota);

#endif