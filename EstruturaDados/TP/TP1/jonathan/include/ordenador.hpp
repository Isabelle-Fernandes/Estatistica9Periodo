#ifndef ORDENADOR_HPP
#define ORDENADOR_HPP

#include "sortperf.hpp" 

// ---------- Funções principais ----------

// Essa é a função  que escolhe o melhor método de ordenação (Insertion ou Quick com mediana de 3).
// Leva em conta dois limiares: o tamanho mínimo da partição e o limite de quebras.
// É o coração do algoritmo adaptativo.
void ordenadorUniversal(int *vet, int tam, int minPart, int limQuebras, sortperf_t *perf);

// Faz experimentos para descobrir qual o melhor valor para minPart (limiar da partição).
// Tenta encontrar um ponto ótimo onde o custo (a*cmp + b*move + c*calls) fica abaixo do limiar definido.
int determinaLimiarParticao(int *vetOriginal, int tam, double limiarCusto, double a, double b, double c);

// Similar à anterior, mas busca o melhor valor para o número máximo de quebras (partições desbalanceadas).
// Considera também um limiar de custo e a semente para embaralhamento (seed).
int determinaLimiarQuebras(double limiarCusto, int *vetOriginal, int tam, int limPart, double a, double b, double c, int seed);


// ---------- Funções auxiliares ----------

// Conta quantas "quebras" o vetor possui — ou seja, quantas vezes a ordem crescente foi violada.
// Por exemplo: 3, 2, 5, 4 → tem 2 quebras (entre 3-2 e 5-4)
int contaQuebras(int *vet, int tam);

// Algoritmo clássico de ordenação por inserção, eficiente para vetores pequenos.
// Ordena o intervalo fechado [l, r] e registra as operações na struct sortperf_t.
void insertionSort(int v[], int l, int r, sortperf_t *s);

// Quicksort com mediana de 3 e fallback para Insertion Sort quando a partição é pequena demais.
// Usa minPart para decidir quando parar de particionar.
void quickSort3Ins(int *A, int l, int r, int minPart, sortperf_t *s);

// Realiza a partição ternária de Dijkstra, dividindo em três zonas: < pivo, == pivo, > pivo.
// Retorna os limites das regiões via ponteiros i e j.
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s);

// Retorna o valor da mediana entre três inteiros (a, b, c).
// Muito usada para escolher pivôs mais estáveis no Quicksort.
int median(int a, int b, int c);

// Troca o valor de dois elementos de forma segura, incrementando o contador de movimentações.
void swap(int *xp, int *yp, sortperf_t *s);

// Dada uma partição ótima (limParticao) e um vetor de valores medianos por subvetor (mpsValores),
// calcula nova faixa para testar valores de minPart (minMPS, maxMPS e o passo para iteração).
// Usado na calibragem automática dos limiares.
void calculaNovaFaixa(int limParticao, int *mpsValores, int &minMPS, int &maxMPS, int &passoMPS);

#endif