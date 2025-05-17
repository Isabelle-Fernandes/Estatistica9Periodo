#ifndef CUSTOPARTICAO_H
#define CUSTOPARTICAO_H

#include "Vetor.hpp"

class CustoParticao {
public:
    CustoParticao(int _particao, double _custo, int _comparacoes, int _movimentacoes, int _chamadas);
    ~CustoParticao();
    int particao;
    double custo;
    int comparacoes;
    int movimentacoes;
    int chamadas;
};

#endif
