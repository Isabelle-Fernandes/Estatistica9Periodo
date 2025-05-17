#ifndef VETOR_H
#define VETOR_H

class Vetor {
public:
    Vetor(const Vetor &copia); // construtor de copia de um vetor para o outro
    Vetor(int tamanho);
    ~Vetor();

    int *vetor;
    int tam;

    int chamadas;
    int comparacoes;
    int movimentacoes;
 
    void inccalls(int num);
    void inccmp(int num);
    void incmov(int num);
    void resetCounter();
    void InduzirQuebras(int numQuebras, int seed);
    int breaks();
};

#endif
