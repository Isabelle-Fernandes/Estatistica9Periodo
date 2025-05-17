#include "LimiarParticao.hpp"
#include <cmath>
#include <iomanip>

LimiarParticao::LimiarParticao(double _parametroA, double _parametroB, double _parametroC){
    for (int i = 0; i < NUM_FAIXAS; i++){
        custoParticao[i] = new CustoParticao(0, 0, 0, 0, 0);
    }
    this->parametroA = _parametroA;
    this->parametroB = _parametroB;
    this->parametroC = _parametroC;
}

LimiarParticao::~LimiarParticao(){
    for (int i = 0; i < NUM_FAIXAS; i++){
        delete custoParticao[i];
    }
}

int LimiarParticao::DeterminaLimiarParticao(Vetor &vetor, int tam, double limiarCusto){
    int minMPS = 2;
    int maxMPS = tam;
    int passoMPS = (maxMPS-minMPS ) / 5;
    float diffCusto = limiarCusto + 1;
    int numMPS = 5;
    int limParticao;
    int iteracao = 0;
    int limParticaoAntesCalculaFaixa = 0;

    while ((diffCusto > limiarCusto) && (numMPS >= 5)){
        numMPS = 0;
        for (int t = minMPS; t <= maxMPS; t+=passoMPS){
            Vetor vetorCopia = Vetor(vetor); // crio uma copia do vetor para ele nao somar os inccals, comp, move em cada for e está conforme o original desordenado
            this->ordenadorUniversal.Ordena(vetorCopia, tam, t, tam, tam);
            this->registraEstatisticas(numMPS, vetorCopia, t);
            numMPS++;
        }
        limParticao = this->menorCusto(numMPS);
        limParticaoAntesCalculaFaixa = limParticao;
        this->CalculaNovaFaixa(limParticao, minMPS, maxMPS, passoMPS, numMPS);
        diffCusto = fabs(this->custoParticao[limParticao]->custo - this->custoParticao[limParticao + 2]->custo);
        this->ImprimeEstatisticas(iteracao, limParticaoAntesCalculaFaixa, diffCusto, numMPS);
        iteracao++;
    }
    
    return this->custoParticao[limParticaoAntesCalculaFaixa]->particao;
}

double LimiarParticao::calculaCusto(int _movimentacoes, int _comparacoes, int _chamadas){
    double custo = (this->parametroA * _comparacoes) + (this->parametroB * _movimentacoes) + (this->parametroC * _chamadas);
    return custo;
}

void LimiarParticao::registraEstatisticas(int index, Vetor &vetor, int tamParticao){
    custoParticao[index]->particao = tamParticao;
    custoParticao[index]->comparacoes = vetor.comparacoes;
    custoParticao[index]->movimentacoes = vetor.movimentacoes;
    custoParticao[index]->chamadas = vetor.chamadas;
    custoParticao[index]->custo = calculaCusto(vetor.movimentacoes, vetor.comparacoes, vetor.chamadas);   
}

void LimiarParticao::ImprimeEstatisticas(int _iteracao, int _limiteParticao, double _diffCusto, int _numMPS){
    std::cout << "iter " << _iteracao << std::endl;
    for (int i = 0; i < _numMPS; i++){
        std::cout << "mps " << this->custoParticao[i]->particao << " ";
        std::cout << "cost " << std::fixed << std::setprecision(9) << this->custoParticao[i]->custo << " ";
        std::cout << "cmp " << this->custoParticao[i]->comparacoes << " ";
        std::cout << "move " << this->custoParticao[i]->movimentacoes << " ";
        std::cout << "calls " << this->custoParticao[i]->chamadas << std::endl;
    }
    std::cout << "nummps " << _numMPS << " ";
    std::cout << "limParticao " << this->custoParticao[_limiteParticao]->particao << " ";
    std::cout << "mpsdiff " << std::fixed << std::setprecision(6) << _diffCusto << std::endl;
    std::cout << std::endl;

}

int LimiarParticao::menorCusto(int _numMPS){
    double menor = custoParticao[0]->custo;
    int index = 0;
    for (int i = 1; i < _numMPS; i++){
        if (custoParticao[i]->custo < menor){
            menor = custoParticao[i]->custo;
            index = i;
        }
    }
    return index;
}

void LimiarParticao::CalculaNovaFaixa(int &_limParticao, int &_minMPS, int &_maxMPS, int &_passoMPS, int _numMPS){
    int newMin, newMax;
    if (_limParticao == 0){
        newMin = 0;
        newMax = 2;
    } else if (_limParticao == _numMPS - 1){
        newMin = _numMPS - 3;
        newMax = _numMPS - 1;
    } else {
        newMin = _limParticao - 1;
        newMax = _limParticao + 1;
    }
    _minMPS = this->custoParticao[newMin]->particao;
    _maxMPS = this->custoParticao[newMax]->particao;
    _passoMPS = (int) (_maxMPS - _minMPS) / 5;
    if (_passoMPS == 0) _passoMPS = 1;
    _limParticao = newMin;

}