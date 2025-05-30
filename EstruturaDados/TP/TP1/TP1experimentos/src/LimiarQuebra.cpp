#include "LimiarQuebra.hpp"
#include <cmath>
#include <iomanip>

LimiarQuebra::LimiarQuebra(double _parametroA, double _parametroB, double _parametroC){
    for (int i = 0; i < (NUM_FAIXAS); i++){
        custoQuebra[i] = new CustoQuebra(0, 0, 0, 0, 0);
    }
    this->parametroA = _parametroA;
    this->parametroB = _parametroB;
    this->parametroC = _parametroC;
}

LimiarQuebra::~LimiarQuebra(){
    for (int i = 0; i < (NUM_FAIXAS); i++){
        delete custoQuebra[i];
    }
}

int LimiarQuebra::DeterminaLimiarQuebra(Vetor &vetor, int tam, double limiarCusto, int tamMinParticao, int seed){
    int minMQS = 1;
    int maxMQS = tam/2;
    int passoMQS = (maxMQS-minMQS) / 5;
    float diffCusto = limiarCusto + 1;
    int numMQS = 10;
    int limQuebras;
    int iteracao = 0;
    int limQuebrasAntesCalculaFaixa;

    while ((diffCusto > limiarCusto) && (numMQS >= 10)){
        int esq = 0;
        int dir = tam - 1;
        numMQS = 0;
        
        for (int t = minMQS; t <= maxMQS; t+=passoMQS){
            Vetor vetorQuebras = Vetor(vetor); // crio uma copia do vetor para ser quebrado com o indutor de quebras
            vetorQuebras.InduzirQuebras(t, seed); 
            Vetor vetorInsertion = Vetor(vetorQuebras); // crio uma copia do vetor para ser ordenado com o insertion
            Vetor vetorQuicksortIns = Vetor(vetorQuebras); // crio uma copia do vetor para ser ordenado com o quicksortIns
            quicksortIns.quickSort3Ins(vetorQuicksortIns, esq, dir, tamMinParticao);
            insertion.insertionSort(vetorInsertion, esq, dir);
            this->registraEstatisticas(numMQS, vetorQuicksortIns, t);
            this->registraEstatisticas(numMQS+1, vetorInsertion, t);
            numMQS += 2;
        }
        limQuebras = this->menorCusto(numMQS);
        limQuebrasAntesCalculaFaixa = limQuebras;
        this->CalculaNovaFaixa(limQuebras, minMQS, maxMQS, passoMQS, numMQS);
        diffCusto = calculaDiffCusto(limQuebras);
        iteracao++;
    }
    return this->custoQuebra[limQuebrasAntesCalculaFaixa]->quebra;
}

double LimiarQuebra::calculaCusto(int _movimentacoes, int _comparacoes, int _chamadas){
    double custo = (this->parametroA * _comparacoes) + (this->parametroB * _movimentacoes) + (this->parametroC * _chamadas);
    return custo;
}

void LimiarQuebra::registraEstatisticas(int _index, Vetor &vetor, int numQuebras){
    custoQuebra[_index]->quebra = numQuebras;
    custoQuebra[_index]->comparacoes = vetor.comparacoes;
    custoQuebra[_index]->movimentacoes = vetor.movimentacoes;
    custoQuebra[_index]->chamadas = vetor.chamadas;
    custoQuebra[_index]->custo = calculaCusto(vetor.movimentacoes, vetor.comparacoes, vetor.chamadas);   
}

int LimiarQuebra::menorCusto(int _numMQS){
    double menor = fabs(custoQuebra[0]->custo - custoQuebra[1]->custo);
    int index = 0;
    for (int i = 2; i < _numMQS; i+=2){
        double proximo = fabs(custoQuebra[i]->custo - custoQuebra[i+1]->custo);
        if (proximo < menor){
            menor = proximo;
            index = i;
        }
    }
    return index;
}

void LimiarQuebra::CalculaNovaFaixa(int &_limQuebras, int &_minMQS, int &_maxMQS, int &_passoMQS, int _numMQS){
    int newMin, newMax;
    if (_limQuebras == 0){
        newMin = 0;
        newMax = 4;
    } else if (_limQuebras == _numMQS - 2){
        newMin = _numMQS - 6;
        newMax = _numMQS - 2;
    } else {
        newMin = _limQuebras - 2;
        newMax = _limQuebras + 2;
    }
    _minMQS = this->custoQuebra[newMin]->quebra;
    _maxMQS = this->custoQuebra[newMax]->quebra;
    _passoMQS = (int) (_maxMQS - _minMQS) / 5;
    if (_passoMQS == 0) _passoMQS = 1;
    _limQuebras = newMin;

}

float LimiarQuebra::calculaDiffCusto(int _limQuebras){
    double custoMenor = this->custoQuebra[_limQuebras]->custo;
    double custoMaior = this->custoQuebra[_limQuebras]->custo;

    for (int i = (_limQuebras+1); i < (_limQuebras+6); i++){
        double proximo = this->custoQuebra[i]->custo;
        
        if (proximo > custoMaior){
            custoMaior = proximo;
        }
        if (proximo < custoMenor){
            custoMenor = proximo;
        }
    }
    return (custoMaior - custoMenor);
}