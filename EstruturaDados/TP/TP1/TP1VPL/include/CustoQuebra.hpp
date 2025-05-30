#ifndef CUSTOQUEBRA_H
#define CUSTOQUEBRA_H

#include "Vetor.hpp"

class CustoQuebra {
public:
    CustoQuebra(int _quebra, double _custo, int _comparacoes, int _movimentacoes, int _chamadas);
    ~CustoQuebra();
    int quebra;
    double custo;
    int comparacoes;
    int movimentacoes;
    int chamadas;
};

#endif
