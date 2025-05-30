#ifndef LIMIARQUEBRA_H
#define LIMIARQUEBRA_H

#include "OrdenadorUniversal.hpp"
#include "CustoQuebra.hpp"
#include <iostream>

class LimiarQuebra {
public:
    static const int NUM_FAIXAS = 20; // coloquei para mais, uma vez que pode ultrapassar o limite de 12 faixas (6 para ins e 6 para quick)
    double parametroA; // oeficientes da funcao custo que eh dado na entrada do programa
    double parametroB; // coeficientes da funcao custo que eh dado na entrada do programa
    double parametroC; // coeficientes da funcao custo que eh dado na entrada do programa
    Insertion insertion;
    QuicksortIns quicksortIns;
    CustoQuebra *custoQuebra[NUM_FAIXAS]; // coloquei um vetor maior que 12 pois ele pode ter mais de 12 faixas na iteracao
    LimiarQuebra(double _parametroA, double _parametroB, double _parametroC);
    ~LimiarQuebra();
    int DeterminaLimiarQuebra(Vetor &vetor, int tam, double limiarCusto, int tamMinParticao, int seed);
    int menorCusto(int _numMQS);
    float calculaDiffCusto(int _limQuebras);
    void registraEstatisticas(int _numMQS, Vetor &vetor, int numQuebras);
    double calculaCusto(int _movimentacoes, int _comparacoes, int _chamadas);
    void CalculaNovaFaixa(int &_limiteQuebras, int &_minMQS, int &_maxMQS, int &_passoMQS, int _numMQS);

};

#endif