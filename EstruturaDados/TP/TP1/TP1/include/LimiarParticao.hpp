#ifndef LIMIARPARTICAO_H
#define LIMIARPARTICAO_H

#include "OrdenadorUniversal.hpp"
#include "CustoParticao.hpp"
#include <iostream>

class LimiarParticao {
public:
    static const int NUM_FAIXAS = 12; // coloquei para mais, uma vez que pode ultrapassar o limite de 6 faixas
    double parametroA; // sao os coeficientes da funcao custo que eh dado na entrada do programa
    double parametroB; // sao os coeficientes da funcao custo que eh dado na entrada do programa
    double parametroC; // sao os coeficientes da funcao custo que eh dado na entrada do programa
    CustoParticao *custoParticao[NUM_FAIXAS];
    LimiarParticao(double _parametroA, double _parametroB, double _parametroC);
    ~LimiarParticao();
    OrdenadorUniversal ordenadorUniversal;
    int DeterminaLimiarParticao(Vetor &vetor, int tam, double limiarCusto);
    int menorCusto(int _numMPS);
    void registraEstatisticas(int index, Vetor &vetor, int tamParticao);
    double calculaCusto(int _movimentacoes, int _comparacoes, int _chamadas);
    void ImprimeEstatisticas(int _iteracao, int _limiteParticao, double _diffCusto, int _numMPS);
    void CalculaNovaFaixa(int &_limParticao, int &_minMPS, int &_maxMPS, int &_passoMPS, int _numMPS);

};

#endif